# Custom target: pio run -e esp32dev_secure -t upload-signed
# Builds, then flashes the signed bootloader, partition table, and signed app.
# Offsets come from flasher_args.json so they match this build.

Import("env")
import json
import os
import sys
from pathlib import Path


def log(msg: str) -> None:
    print(msg, flush=True)


def esptool() -> list[str]:
    venv = Path.home() / ".dicewallet" / "esptools" / "bin" / "esptool"
    if venv.is_file():
        return [str(venv)]
    script = Path.home() / ".platformio" / "packages" / "tool-esptoolpy" / "esptool"
    python = Path.home() / ".platformio" / "penv" / "bin" / "python"
    if script.is_file() and python.is_file():
        return [str(python), str(script)]
    raise SystemExit("esptool not found")


def upload_signed(source, target, env):
    del source, target
    build_dir = Path(env.subst("$BUILD_DIR"))
    args_path = build_dir / "flasher_args.json"
    if not args_path.is_file():
        raise SystemExit(f"missing {args_path}; build first")

    signed_app = build_dir / "firmware.signed.bin"
    signed_boot = build_dir / "bootloader.signed.bin"
    if not signed_app.is_file() or not signed_boot.is_file():
        raise SystemExit("signed images missing; run the secure build so sign_firmware.py runs")

    args = json.loads(args_path.read_text())
    flash = args["flash_files"]
    parts = None
    for offset, name in flash.items():
        if name.endswith("partitions.bin"):
            parts = (offset, build_dir / Path(name).name)
    if parts is None:
        raise SystemExit("partition table offset not found in flasher_args.json")

    app_offset = None
    boot_offset = None
    for offset, name in flash.items():
        base = Path(name).name
        if base == "firmware.bin":
            app_offset = offset
        elif base == "bootloader.bin":
            boot_offset = offset
    if app_offset is None or boot_offset is None:
        raise SystemExit("bootloader or app offset not found in flasher_args.json")

    port = env.subst("$UPLOAD_PORT") or env.subst("$MONITOR_PORT") or os.environ.get("UPLOAD_PORT", "")
    speed = env.subst("$UPLOAD_SPEED") or "921600"
    cmd = esptool() + ["--chip", "esp32", "--baud", speed]
    if port and port not in ("", "none"):
        cmd += ["--port", port]
    cmd += [
        "write_flash",
        boot_offset, str(signed_boot),
        parts[0], str(parts[1]),
        app_offset, str(signed_app),
    ]
    log("secure boot: flashing signed bootloader, partitions, and app")
    log(" ".join(cmd))
    env.Execute(env.VerboseAction(cmd, "Uploading signed images"))


env.AddCustomTarget(
    name="upload-signed",
    dependencies=["buildprog"],
    actions=[env.Action(upload_signed)],
    title="Build and upload signed bootloader, partitions, and app",
    description="Flash firmware.signed.bin, bootloader.signed.bin, and partitions.bin",
)