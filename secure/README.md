# Secure Boot keys

This directory holds the **public** key used to verify signed DiceWallet firmware.
It does not hold the private key.

| File | What it is |
|------|------------|
| `dicewallet-secure-boot.pub.pem` | Secure Boot v2 public key. Safe to publish. Used to verify a signed image. |
| `secure_boot_signing_key.pem` | Private key. **Not in this repository.** Signs images. Losing it bricks every board burned with its digest. |

The private key lives outside the tree, for example `~/.dicewallet/secure_boot_signing_key.pem`, or wherever the `DICEWALLET_SIGNING_KEY` environment variable points to.

## What the public key is

`dicewallet-secure-boot.pub.pem` is the RSA-3072 public half of the Secure Boot v2 signing key. Anyone can use it to check that a `.signed.bin` was signed by the matching private key. It cannot sign firmware, and it cannot burn a device.

A valid signature proves the file came from the holder of that private key. It does not prove the firmware is safe. Compare this public key against the copy first published with the project, not against a key from a random fork.

## Verify a signed image

Download the signed release file and this public key. From the project root run the followign command, but use the correct bin path to esptools, and the correct .bin file path.

```bash
~/.dicewallet/esptools/bin/espsecure verify-signature --version 2 \
  --keyfile secure/dicewallet-secure-boot.pub.pem \
  dicewallet-<version>-esp32dev_secure.signed.bin
```