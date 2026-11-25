# Pre-build script for esp32dev_secure: find the Secure Boot v2 signing key.
#
# Order: the DICEWALLET_SIGNING_KEY environment variable, then
# ~/.dicewallet/secure_boot_signing_key.pem. The key never lives in the repo.
#
# The secure build stops if the key is missing. An unsigned "secure" image
# would not boot on a board with Secure Boot enabled, and on a fresh board it
# would silently stay unprotected.

Import("env")
import os
import sys
from pathlib import Path

DEFAULT_KEY = Path.home() / ".dicewallet" / "secure_boot_signing_key.pem"


def log(msg: str) -> None:
    print(msg, flush=True)


raw = os.environ.get("DICEWALLET_SIGNING_KEY", "")
path = Path(raw).expanduser() if raw else DEFAULT_KEY

if not path.is_file():
    sys.stderr.write(
        f"secure boot: signing key not found: {path}\n"
        "Set DICEWALLET_SIGNING_KEY to the PEM file, or create one with:\n"
        "  mkdir -p ~/.dicewallet\n"
        "  espsecure generate-signing-key --version 2 --scheme rsa3072 "
        "~/.dicewallet/secure_boot_signing_key.pem\n"
    )
    env.Exit(1)

if " " in str(path.resolve()):
    sys.stderr.write(f"secure boot: the key path must not contain spaces: {path}\n")
    env.Exit(1)

# espidf.py reads this before falling back to CONFIG_SECURE_BOOT_SIGNING_KEY,
# and uses it to sign the bootloader, partition table and app.
env["PIO_ESP32_SECURE_BOOT_SIGNING_KEY"] = str(path.resolve())
log(f"secure boot: signing with {path}")
