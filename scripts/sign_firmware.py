#!/usr/bin/env python3
"""Sign the ESP32 bootloader and app when a Secure Boot v2 key is available.

The key is not in the repository. Set DICEWALLET_SIGNING_KEY, or place the PEM at
~/.dicewallet/secure_boot_signing_key.pem. If neither exists, this script prints
a notice and leaves the image unsigned so a development build still succeeds.

PlatformIO runs this after firmware.bin exists. Signing appends a signature
block. It does not change the app validation hash that firmware_hash.py prints.
"""

import os
import shutil
import subprocess
import sys
from pathlib import Path


def signing_key() -> Path | None:
    env = os.environ.get("DICEWALLET_SIGNING_KEY")
    if env:
        path = Path(env).expanduser()
        return path if path.is_file() else None
    default = Path.home() / ".dicewallet" / "secure_boot_signing_key.pem"
    return default if default.is_file() else None


def espsecure() -> list[str]:
    venv = Path.home() / ".dicewallet" / "esptools" / "bin" / "espsecure"
    if venv.is_file():
        return [str(venv)]
    script = Path.home() / ".platformio" / "packages" / "tool-esptoolpy" / "espsecure"
    python = Path.home() / ".platformio" / "penv" / "bin" / "python"
    if not python.is_file():
        python = Path(sys.executable)
    if script.is_file():
        return [str(python), str(script)]
    found = shutil.which("espsecure")
    if found:
        return [sys.executable, found]
    raise SystemExit("espsecure not found. Install esptool in ~/.dicewallet/esptools.")


def sign(src: Path, dest: Path, key: Path) -> None:
    cmd = espsecure() + [
        "sign-data",
        "--version", "2",
        "--keyfile", str(key),
        "--output", str(dest),
        str(src),
    ]
    subprocess.run(cmd, check=True)


def versioned_signed(app: Path, env_name: str, root: Path) -> Path:
    text = (root / "include" / "app" / "version.h").read_text()
    version = "unknown"
    for line in text.splitlines():
        if "DICEWALLET_VERSION" in line and '"' in line:
            version = line.split('"')[1]
            break
    return app.with_name(f"dicewallet-{version}-{env_name}.signed.bin")


def log(msg: str) -> None:
    print(msg, flush=True)


def sign_build(build_dir: Path, env_name: str, root: Path) -> None:
    key = signing_key()
    if key is None:
        log("secure boot: key not present, image unsigned")
        return
    log(f"secure boot: signing with {key}")
    app = build_dir / "firmware.bin"
    bootloader = build_dir / "bootloader.bin"
    if not app.is_file():
        log(f"secure boot: {app.name} not built yet, skipping")
        return
    sign(app, app.with_suffix(".signed.bin"), key)
    log(f"secure boot: signed {app.with_suffix('.signed.bin')}")
    if bootloader.is_file():
        sign(bootloader, bootloader.with_suffix(".signed.bin"), key)
        log(f"secure boot: signed {bootloader.with_suffix('.signed.bin')}")
    signed = versioned_signed(app, env_name, root)
    shutil.copyfile(app.with_suffix(".signed.bin"), signed)
    log(f"secure boot: wrote {signed}")


def main() -> None:
    root = Path(__file__).resolve().parents[1]
    build_dir = Path(sys.argv[1] if len(sys.argv) > 1 else root / ".pio/build/esp32dev")
    env_name = sys.argv[2] if len(sys.argv) > 2 else build_dir.name
    sign_build(build_dir, env_name, root)


_ran = False


def _after_build(source, target, env):
    global _ran
    if _ran:
        return
    del source, target
    root = Path(env.subst("$PROJECT_DIR"))
    build_dir = Path(env.subst("$BUILD_DIR"))
    env_name = env.subst("$PIOENV") or build_dir.name
    before = (build_dir / "firmware.signed.bin").exists()
    sign_build(build_dir, env_name, root)
    if (build_dir / "firmware.signed.bin").exists() and not before:
        _ran = True
    elif (build_dir / "firmware.signed.bin").exists():
        _ran = True
    sys.stdout.flush()


try:
    Import("env")
except NameError:
    if __name__ == "__main__":
        main()
else:
    log("secure boot: sign_firmware.py loaded")
    # checkprogsize runs on every pio run, including when nothing is rebuilt.
    # The .bin action only runs when firmware.bin is regenerated.
    env.AddPostAction("checkprogsize", _after_build)
    env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", _after_build)
    env.AddPostAction("buildprog", _after_build)