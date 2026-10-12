# Official vector tests

Unity tests, run on the ESP32. They use the Arduino `String` and the ESP-IDF mbedTLS. There is no host shim.

```bash
pio test -e esp32dev_test
```

`esp32dev_test` builds `src/bip39` and `src/coins` only, so `main.cpp`'s `setup()` does not collide with Unity.

Sources for `vectors/`:

- BIP39 English, passphrase `TREZOR`: [trezor/python-mnemonic vectors.json](https://github.com/trezor/python-mnemonic/blob/master/vectors.json), cited by [BIP-0039](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki).
- BIP32 vectors 1–4: [BIP-0032](https://github.com/bitcoin/bips/blob/master/bip-0032.mediawiki#test-vectors). Vector 5 is invalid-key parsing, which this firmware does not implement.
- SLIP-0132 account xpub/ypub/zpub, empty passphrase: [SLIP-0132](https://github.com/satoshilabs/slips/blob/master/slip-0132.md).
