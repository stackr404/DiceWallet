#pragma once

// BIP39 passphrase salt is "mnemonic" + passphrase. This firmware has no NFKD,
// so only printable ASCII is accepted. 128 matches the derivation buffer.
static constexpr int kPassphraseMax = 128;