#!/usr/bin/env python3
"""Copy the signed app to a versioned release name (esp32dev_secure only).

PlatformIO itself signs the images when CONFIG_SECURE_BOOT_BUILD_SIGNED_BINARIES
is set (see sdkconfig.defaults and scripts/ask_signing_key.py). This script only
checks that the signed app exists and writes:

    .pio/build/esp32dev_secure/dicewallet-<version>-esp32dev_secure.signed.bin

Signing appends a signature block. It does not change the app validation hash
that firmware_hash.py prints and the About screen shows.
"""

import re
import shutil
import sys
from pathlib import Path


def log(msg: str) -> None:
    print(msg, flush=True)


def firmware_version(root: Path) -> str:
    text = (root / "include" / "app" / "version.h").read_text()
    match = re.search(r'DICEWALLET_VERSION\s+"([^"]+)"', text)
    return match.group(1) if match else "unknown"


def copy_signed(build_dir: Path, env_name: str, root: Path) -> Path:
    signed = build_dir / "firmware-signed.bin"
    if not signed.is_file():
        raise SystemExit(f"secure boot: {signed} is missing; the app was not signed")
    dest = build_dir / f"dicewallet-{firmware_version(root)}-{env_name}.signed.bin"
    shutil.copyfile(signed, dest)
    return dest


def main() -> None:
    root = Path(__file__).resolve().parents[1]
    build_dir = Path(sys.argv[1] if len(sys.argv) > 1 else root / ".pio/build/esp32dev_secure")
    env_name = sys.argv[2] if len(sys.argv) > 2 else build_dir.name
    log(f"secure boot: wrote {copy_signed(build_dir, env_name, root)}")


def _after_signed(source, target, env):
    del source, target
    root = Path(env.subst("$PROJECT_DIR"))
    build_dir = Path(env.subst("$BUILD_DIR"))
    env_name = env.subst("$PIOENV") or build_dir.name
    log(f"secure boot: wrote {copy_signed(build_dir, env_name, root)}")


try:
    Import("env")
except NameError:
    if __name__ == "__main__":
        main()
else:
    # buildprog depends on the signed image, so it exists once buildprog is done.
    env.AddPostAction("buildprog", _after_signed)
