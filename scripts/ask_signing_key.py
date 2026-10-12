# Resolve the Secure Boot signing key

Import("env")
import os
import sys
from pathlib import Path


def log(msg: str) -> None:
    print(msg, flush=True)


key = os.environ.get("DICEWALLET_SIGNING_KEY", "")
path = Path(key).expanduser() if key else Path.home() / ".dicewallet" / "secure_boot_signing_key.pem"
if not path.is_file():
    log(f"secure boot: signing key not found: {path}")
    log("Set DICEWALLET_SIGNING_KEY or place the PEM at ~/.dicewallet/secure_boot_signing_key.pem")
else:
    os.environ["DICEWALLET_SIGNING_KEY"] = str(path)
    log(f"secure boot: using {path}")