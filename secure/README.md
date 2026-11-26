# Secure Boot keys

This directory holds the **public** key used to verify signed DiceWallet firmware.
It does not hold the private key.

| File | What it is |
|------|------------|
| `dicewallet-secure-boot.pub.pem` | Secure Boot v2 public key. Safe to publish. Used to verify a signed image. |
| `secure_boot_signing_key.pem` | Private key. **Not in this repository.** Signs images. Losing it means no board burned with its digest can ever be updated again. |

The private key lives outside the tree, for example `~/.dicewallet/secure_boot_signing_key.pem`, or wherever the `DICEWALLET_SIGNING_KEY` environment variable points to.

## What the public key is

`dicewallet-secure-boot.pub.pem` is the RSA-3072 public half of the Secure Boot v2 signing key. Anyone can use it to check that a `.signed.bin` was signed by the matching private key. It cannot sign firmware, and it cannot burn a device.

A valid signature proves the file came from the holder of that private key. It does not prove the firmware is safe. Compare this public key against the copy first published with the project, not against a key from a random fork.

## Verify a signed image

Install `esptool` (it includes `espsecure`), download the release files and this public key into one folder, and run:

```bash
espsecure verify-signature --version 2 \
  --keyfile dicewallet-secure-boot.pub.pem \
  dicewallet-<version>-secure-app.bin
```

Repeat for `-secure-bootloader.bin` and `-secure-partitions.bin`. The SHA-256 of this public key file is `79c0f81466f6b9ad0268db99330680b99ec2ee0e9598da69c358fe1f0d5bfb86`.

The main README section [Installing a release](../README.md#installing-a-release) has the full steps for Windows, macOS and Linux: checking the key, the signed checksum list, every file, and flashing.