#!/usr/bin/env python3
"""Build and package a DiceWallet release: signed (Secure Boot) and unsigned.

Usage (from the project root, on the machine that holds the signing key):

    python3 scripts/make_release.py              # build, package, verify
    python3 scripts/make_release.py --no-build   # package the existing builds
    python3 scripts/make_release.py --publish    # also create the GitHub release

Output goes to release/v<version>/:

    dicewallet-<v>-secure-bootloader.bin   signed bootloader      write at 0x1000
    dicewallet-<v>-secure-partitions.bin   signed partition table write at 0xD000
    dicewallet-<v>-secure-app.bin          signed app             write at 0x20000
    dicewallet-<v>-unsigned-full.bin       complete unsigned image write at 0x0
    dicewallet-<v>-unsigned-app.bin        unsigned app only       write at 0x10000
    dicewallet-secure-boot.pub.pem         public key
    SHA256SUMS                             SHA-256 of every file above
    SHA256SUMS.sig                         RSA signature of SHA256SUMS (release key)
    RELEASE-NOTES.md                       hashes and flash commands for this version

Before it finishes, the script checks:
  * every signed image verifies against secure/dicewallet-secure-boot.pub.pem,
    so a release can never be signed with a different key than the one published;
  * SHA256SUMS.sig verifies against the same public key;
  * each app image ends with its own validation hash (the About-screen hash).

Standard library only. Needs PlatformIO (pio), its esptool package, and openssl.
"""

import argparse
import hashlib
import os
import re
import shutil
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PUBLIC_KEY = ROOT / "secure" / "dicewallet-secure-boot.pub.pem"
DEFAULT_KEY = Path.home() / ".dicewallet" / "secure_boot_signing_key.pem"

UNSIGNED_ENV = "esp32dev"
SECURE_ENV = "esp32dev_secure"

# Fixed by the ESP32 ROM and by the two builds.
BOOTLOADER_OFFSET = 0x1000
UNSIGNED_PARTITION_OFFSET = 0x8000  # Arduino default


# A release folder that is still being written; removed if anything fails.
_partial = None


def fail(msg: str) -> None:
    if _partial is not None and _partial.exists():
        shutil.rmtree(_partial)
        msg += f"\nrelease: removed incomplete {_partial}"
    sys.stderr.write(f"release: {msg}\n")
    sys.exit(1)


def run(cmd, **kw) -> subprocess.CompletedProcess:
    print("+ " + " ".join(str(c) for c in cmd), flush=True)
    try:
        return subprocess.run([str(c) for c in cmd], check=True, **kw)
    except subprocess.CalledProcessError as err:
        fail(f"command failed (exit {err.returncode}): {Path(str(cmd[0])).name} {cmd[1] if len(cmd) > 1 else ''}")


def find_tool(name: str, env_var: str, candidates) -> Path:
    if os.environ.get(env_var):
        return Path(os.environ[env_var])
    for c in candidates:
        for p in (c, c.with_suffix(".exe")):
            if p.is_file():
                return p
    found = shutil.which(name)
    if found:
        return Path(found)
    fail(f"{name} not found. Set {env_var} to its path.")


def version() -> str:
    text = (ROOT / "include" / "app" / "version.h").read_text()
    m = re.search(r'DICEWALLET_VERSION\s+"([^"]+)"', text)
    if not m:
        fail("DICEWALLET_VERSION not found in include/app/version.h")
    return m.group(1)


def signing_key() -> Path:
    raw = os.environ.get("DICEWALLET_SIGNING_KEY", "")
    key = Path(raw).expanduser() if raw else DEFAULT_KEY
    if not key.is_file():
        fail(f"signing key not found: {key} (set DICEWALLET_SIGNING_KEY)")
    return key


def git(*args) -> str:
    return subprocess.run(["git", *args], cwd=ROOT, check=True,
                          capture_output=True, text=True).stdout.strip()


def check_tree(allow_dirty: bool) -> str:
    status = git("status", "--porcelain", "--untracked-files=no")
    if status and not allow_dirty:
        fail("working tree has uncommitted changes; commit them first "
             "(or pass --allow-dirty for a test package)")
    return git("rev-parse", "HEAD")


def partitions(path: Path):
    """Yield (name, type, subtype, offset, size) from a partition table binary."""
    data = path.read_bytes()
    for i in range(0, len(data), 32):
        magic, ptype, subtype, offset, size = struct.unpack_from("<HBBII", data, i)
        if magic != 0x50AA:
            break
        name = data[i + 12:i + 28].split(b"\0")[0].decode()
        yield name, ptype, subtype, offset, size


def first_app(table: Path):
    for name, ptype, _sub, offset, size in partitions(table):
        if ptype == 0:
            return offset, size
    fail(f"no app partition in {table}")


def otadata(table: Path):
    for name, ptype, sub, offset, size in partitions(table):
        if ptype == 1 and sub == 0:
            return offset, size
    return None


def sdkconfig_value(name: str) -> str:
    cfg = ROOT / f"sdkconfig.{SECURE_ENV}"
    m = re.search(rf"^CONFIG_{name}=(.*)$", cfg.read_text(), re.M)
    if not m:
        fail(f"CONFIG_{name} not in {cfg}")
    return m.group(1).strip('"')


def validation_hash(app: bytes) -> str:
    """The hash the About screen shows: SHA-256 appended to the app image."""
    body, trailer = app[:-32], app[-32:]
    if hashlib.sha256(body).digest() != trailer:
        fail("app image has no valid appended SHA-256")
    return trailer.hex()


def sha256_file(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--no-build", action="store_true", help="package existing builds")
    ap.add_argument("--allow-dirty", action="store_true", help="allow uncommitted changes")
    ap.add_argument("--publish", action="store_true",
                    help="create GitHub release v<version> with gh (asks first)")
    args = ap.parse_args()

    ver = version()
    key = signing_key()
    commit = check_tree(args.allow_dirty)
    if not PUBLIC_KEY.is_file():
        fail(f"public key missing: {PUBLIC_KEY}")

    home_pio = Path.home() / ".platformio"
    pio = find_tool("pio", "PIO", [home_pio / "penv" / "bin" / "pio",
                                   home_pio / "penv" / "Scripts" / "pio"])
    esptool_dir = home_pio / "packages" / "tool-esptool"
    esptool = find_tool("esptool", "ESPTOOL", [esptool_dir / "esptool"])
    espsecure = find_tool("espsecure", "ESPSECURE", [esptool_dir / "espsecure"])
    openssl = find_tool("openssl", "OPENSSL", [])

    if not args.no_build:
        env = dict(os.environ, DICEWALLET_SIGNING_KEY=str(key))
        run([pio, "run", "-e", UNSIGNED_ENV, "-e", SECURE_ENV], cwd=ROOT, env=env)

    ub = ROOT / ".pio" / "build" / UNSIGNED_ENV
    sb = ROOT / ".pio" / "build" / SECURE_ENV
    for f in (ub / "bootloader.bin", ub / "partitions.bin", ub / "firmware.bin",
              sb / "bootloader-signed.bin", sb / "partitions-signed.bin",
              sb / "firmware.bin", sb / "firmware-signed.bin"):
        if not f.is_file():
            fail(f"missing build output {f}; run without --no-build")

    global _partial
    out = ROOT / "release" / f"v{ver}"
    if out.exists():
        shutil.rmtree(out)
    out.mkdir(parents=True)
    _partial = out
    name = lambda part: out / f"dicewallet-{ver}-{part}.bin"

    # ---- Secure Boot (signed) ----
    secure_part_offset = int(sdkconfig_value("PARTITION_TABLE_OFFSET"), 16)
    secure_app_offset, _ = first_app(sb / "partitions.bin")
    shutil.copyfile(sb / "bootloader-signed.bin", name("secure-bootloader"))
    shutil.copyfile(sb / "partitions-signed.bin", name("secure-partitions"))
    shutil.copyfile(sb / "firmware-signed.bin", name("secure-app"))

    secure_plain = (sb / "firmware.bin").read_bytes()
    if not (sb / "firmware-signed.bin").read_bytes().startswith(secure_plain):
        fail("firmware-signed.bin does not contain firmware.bin; rebuild")
    secure_hash = validation_hash(secure_plain)

    # ---- Unsigned ----
    unsigned_app_offset, app_size = first_app(ub / "partitions.bin")
    unsigned_app = (ub / "firmware.bin").read_bytes()
    if len(unsigned_app) > app_size:
        fail("unsigned app does not fit its partition")
    unsigned_hash = validation_hash(unsigned_app)
    shutil.copyfile(ub / "firmware.bin", name("unsigned-app"))

    merge = [BOOTLOADER_OFFSET, ub / "bootloader.bin",
             UNSIGNED_PARTITION_OFFSET, ub / "partitions.bin"]
    ota = otadata(ub / "partitions.bin")
    if ota:
        # Blank otadata = boot the first app slot, like Arduino's boot_app0.bin.
        blank = ub / "ota_data_blank.bin"
        blank.write_bytes(b"\xff" * ota[1])
        merge += [ota[0], blank]
    merge += [unsigned_app_offset, ub / "firmware.bin"]
    run([esptool, "--chip", "esp32", "merge-bin", "-o", name("unsigned-full"),
         "--flash-mode", "keep", "--flash-freq", "keep", "--flash-size", "keep",
         *[hex(x) if isinstance(x, int) else x for x in merge]])

    shutil.copyfile(PUBLIC_KEY, out / PUBLIC_KEY.name)

    # ---- Checks against the published public key ----
    for part in ("secure-bootloader", "secure-partitions", "secure-app"):
        run([espsecure, "verify-signature", "--version", "2",
             "--keyfile", PUBLIC_KEY, name(part)])

    files = sorted(p for p in out.iterdir() if p.is_file())
    sums = out / "SHA256SUMS"
    sums.write_text("".join(f"{sha256_file(p)}  {p.name}\n" for p in files))
    sig = out / "SHA256SUMS.sig"
    run([openssl, "dgst", "-sha256", "-sign", key, "-out", sig, sums])
    run([openssl, "dgst", "-sha256", "-verify", PUBLIC_KEY, "-signature", sig, sums])

    digest_file = out / "key-digest.tmp"
    run([espsecure, "digest-sbv2-public-key", "--keyfile", PUBLIC_KEY, "-o", digest_file])
    digest_hex = digest_file.read_bytes().hex()
    digest_file.unlink()

    notes = out / "RELEASE-NOTES.md"
    notes.write_text(f"""# DiceWallet {ver}

Built from commit `{commit}`.

See the README section **Installing a release** for full instructions,
including how to verify these files before flashing.

## Choose one version

| Version | About screen hash (Settings → About) |
|---------|--------------------------------------|
| Secure Boot (signed) | `{secure_hash}` |
| Unsigned | `{unsigned_hash}` |

**Secure Boot is permanent.** The first boot of the signed version burns the
digest of the DiceWallet release key into the ESP32's eFuses. From then on the
board only runs firmware signed by that key, so you can only install official
DiceWallet releases on it. You can never go back to unsigned or self-built
firmware on that board.

## Files

| File | Write at |
|------|----------|
| `dicewallet-{ver}-secure-bootloader.bin` | `0x{BOOTLOADER_OFFSET:x}` |
| `dicewallet-{ver}-secure-partitions.bin` | `0x{secure_part_offset:x}` |
| `dicewallet-{ver}-secure-app.bin` | `0x{secure_app_offset:x}` |
| `dicewallet-{ver}-unsigned-full.bin` | `0x0` |
| `dicewallet-{ver}-unsigned-app.bin` | `0x{unsigned_app_offset:x}` (update only) |
| `dicewallet-secure-boot.pub.pem` | release public key |
| `SHA256SUMS`, `SHA256SUMS.sig` | checksums, signed with the release key |

Secure Boot key digest (written to eFuse BLOCK2 on first boot):
`{digest_hex}`

## Flash (replace PORT)

Secure Boot, first install:

    esptool --chip esp32 --port PORT write-flash --flash-mode keep --flash-freq keep --flash-size keep 0x{BOOTLOADER_OFFSET:x} dicewallet-{ver}-secure-bootloader.bin 0x{secure_part_offset:x} dicewallet-{ver}-secure-partitions.bin 0x{secure_app_offset:x} dicewallet-{ver}-secure-app.bin

Secure Boot, update a board that already runs a signed release:

    esptool --chip esp32 --port PORT write-flash --flash-mode keep --flash-freq keep --flash-size keep 0x{secure_app_offset:x} dicewallet-{ver}-secure-app.bin

Unsigned:

    esptool --chip esp32 --port PORT write-flash --flash-mode keep --flash-freq keep --flash-size keep 0x0 dicewallet-{ver}-unsigned-full.bin
""")

    _partial = None  # complete and verified
    print(f"\nRelease v{ver} written to {out}")
    for p in sorted(out.iterdir()):
        print(f"  {p.name}")
    print(f"\nAbout hash, secure:   {secure_hash}")
    print(f"About hash, unsigned: {unsigned_hash}")
    print(f"Key digest (BLOCK2):  {digest_hex}")

    if args.publish:
        tag = f"v{ver}"
        if args.allow_dirty:
            fail("--publish cannot be combined with --allow-dirty")
        git("fetch", "-q", "origin")
        if not git("branch", "-r", "--contains", commit):
            fail(f"commit {commit[:12]} is not on GitHub yet; push it first")
        assets = [p for p in sorted(out.iterdir()) if p.name != "RELEASE-NOTES.md"]
        answer = input(f"\nCreate GitHub release {tag} at {commit[:12]} "
                       f"with {len(assets)} files? Type 'yes': ")
        if answer.strip() != "yes":
            print("Not published.")
            return
        run(["gh", "release", "create", tag, "--target", commit,
             "--title", f"DiceWallet {ver}", "--notes-file", notes, *assets], cwd=ROOT)


if __name__ == "__main__":
    main()
