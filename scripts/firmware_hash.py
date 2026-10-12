#!/usr/bin/env python3
"""Print the SHA-256 the device shows for an ESP32 app image.

esp_partition_get_sha256() returns the validation hash appended to firmware.bin.
That hash is SHA-256 of every byte before the 32-byte trailer, not SHA-256 of
the whole file. Publish this hex next to the release binary.

The build file stays firmware.bin so upload keeps working. A versioned copy is
written beside it: dicewallet-<version>-<env>.bin and a matching .sha256 whose
checksum line names that file.
"""

import hashlib
import re
import shutil
import sys
from pathlib import Path


def validation_hash(blob: bytes) -> bytes:
    if len(blob) <= 32:
        raise SystemExit("image too small")
    body, trailer = blob[:-32], blob[-32:]
    digest = hashlib.sha256(body).digest()
    if digest != trailer:
        raise SystemExit(
            "last 32 bytes are not the SHA-256 of the preceding image; "
            "this is not a plain ESP32 app image"
        )
    return digest


def version_header(root: Path) -> Path:
    return root / "include" / "app" / "version.h"


def firmware_version(root: Path) -> str:
    header = version_header(root)
    match = re.search(r'DICEWALLET_VERSION\s+"([^"]+)"', header.read_text())
    if not match:
        raise SystemExit(f"DICEWALLET_VERSION not found in {header}")
    return match.group(1)


def report(path: Path) -> str:
    digest = validation_hash(path.read_bytes())
    return f"{digest.hex()}  {path.name}"


def write_sum(path: Path) -> Path:
    line = report(path)
    out = path.with_suffix(".sha256")
    out.write_text(line + "\n")
    return out


def versioned_name(env_name: str, version: str) -> str:
    safe_env = re.sub(r"[^A-Za-z0-9_.-]+", "-", env_name)
    return f"dicewallet-{version}-{safe_env}.bin"


def is_versioned(path: Path) -> bool:
    return path.name.startswith("dicewallet-") and path.suffix == ".bin"


def write_versioned(src: Path, env_name: str, root: Path) -> tuple[Path, Path]:
    # An already versioned image keeps its name. firmware.bin is copied.
    dest = src if is_versioned(src) else src.with_name(versioned_name(env_name, firmware_version(root)))
    if dest.resolve() != src.resolve():
        shutil.copyfile(src, dest)
    return dest, write_sum(dest)


def main() -> None:
    root = Path(__file__).resolve().parents[1]
    path = Path(sys.argv[1] if len(sys.argv) > 1 else root / ".pio/build/esp32dev/firmware.bin")
    env_name = sys.argv[2] if len(sys.argv) > 2 else path.parent.name
    print(report(path))
    print(write_sum(path))
    dest, checksum = write_versioned(path, env_name, root)
    print(dest)
    print(checksum)


def _after_build(source, target, env):
    del source, target
    # PlatformIO execs this file, so __file__ is not defined. PROJECT_DIR is.
    root = Path(env.subst("$PROJECT_DIR"))
    path = Path(env.subst("$BUILD_DIR")) / f"{env.subst('${PROGNAME}')}.bin"
    env_name = env.subst("${PIOENV}") or path.parent.name
    line = report(path)
    build_sum = write_sum(path)
    dest, checksum = write_versioned(path, env_name, root)
    print(f"Firmware validation hash: {line}")
    print(f"Wrote {build_sum}")
    print(f"Wrote {dest}")
    print(f"Wrote {checksum}")
    sys.stdout.flush()


try:
    Import("env")
except NameError:
    if __name__ == "__main__":
        main()
else:
    # buildprog finishes after firmware.bin exists. A post-action on the
    # .bin target itself often does not run.
    env.AddPostAction("buildprog", _after_build)