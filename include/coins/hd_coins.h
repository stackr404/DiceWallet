#pragma once

/**
 * hd_coins.h — BIP43/44/49/84/86 + SLIP-0044 / SLIP-0132 registry
 *
 * Account-level extended public key:
 *     m / purpose' / coin_type' / account'
 *
 * Definitions live in hd_coins.cpp. BIP32 HMAC key is always "Bitcoin seed".
 */

#include <stddef.h>
#include <stdint.h>

#ifdef ARDUINO
#include <Arduino.h>
#endif
#include <bip39/bip39_generator.h>

enum hd_algo : uint8_t {
    HD_ALGO_BIP32_SECP256K1 = 1,  // BIP32 / SLIP-0010, secp256k1, xpub exists
    HD_ALGO_SLIP10_ED25519  = 2,  // Ed25519, hardened only, no xpub
    HD_ALGO_CIP1852_ED25519 = 3,  // Cardano account xvk
    HD_ALGO_CRYPTONOTE      = 4,  // Monero view key
    HD_ALGO_SR25519         = 5,  // Bittensor / Substrate
    HD_ALGO_BIP39_SEED32    = 6,  // Canton: Ed25519 from the first 32 seed bytes
    HD_ALGO_TOKEN           = 7   // no own key; watch `host`
};

struct hd_watch_coin {
    const char* code;
    const char* name;
    const char* prefix;     // "zpub", "xpub", "dgub", "" if none
    const char* host;       // "" or "ETH", "ETH,TRX", "XRP,ETH", ...
    uint32_t    purpose;
    uint32_t    coin_type;
    uint8_t     version[4];
    hd_algo      algo;
    bool        this_firmware;
    const char* note;
};


enum hd_script : uint8_t {
    HD_SCRIPT_LEGACY        = 44,  // BIP44  P2PKH
    HD_SCRIPT_NESTED_SEGWIT = 49,  // BIP49  P2SH-P2WPKH
    HD_SCRIPT_NATIVE_SEGWIT = 84,  // BIP84  P2WPKH
    HD_SCRIPT_TAPROOT       = 86   // BIP86  P2TR (usually still serialized as xpub)
};

enum hd_network : uint8_t {
    HD_NETWORK_MAINNET = 0,
    HD_NETWORK_TESTNET = 1
};

/**
 * One coin + script combination.
 * account is not stored here — pass it into derive_account_xpub() (usually 0).
 */
struct coin_type {
  const char* code;
  const char* name;
};

struct hd_coin {
    const char* id;          // stable lookup key, e.g. "btc-zpub"
    const char* name;        // "Bitcoin"
    const char* prefix;      // Base58 payload prefix: "zpub", "xpub", "Ltub"
    uint32_t    purpose;     // BIP43 purpose (44/49/84/86)
    uint32_t    coin_type;    // SLIP-0044
    uint8_t     version[4];  // SLIP-0132 public version bytes
    hd_script    script;
    hd_network   network;
};

extern const hd_watch_coin hd_coin_BTC;
extern const hd_watch_coin hd_coin_ETH;
extern const hd_watch_coin hd_coin_XRP;


/**
 * Writes "m/84'/0'/0'" (NUL-terminated) into out.
 * Returns bytes written excluding NUL, or 0 on truncation.
 */
size_t hd_coin_format_path(char* out, size_t out_len, const hd_watch_coin& coin, uint32_t account = 0);

/** Hardened BIP32 index for a path component. */
inline uint32_t hd_hardened(uint32_t i) {
    return i | 0x80000000u;
}

#ifdef ARDUINO

/**
 * BIP39 seed from mnemonic+passphrase, then the account node for one row of
 * hd_watch_coinS:
 *     m / purpose' / coin_type' / account'
 * serialized with that row's version bytes.
 *
 * Pass any hd_watch_coinS entry. Only rows with
 * algo == HD_ALGO_BIP32_SECP256K1 and this_firmware == true are derived
 * (BTC, ETH, BNB, XRP, TRX, ZEC, DOGE, BCH, LTC, AVAX, CRO, M, MNT).
 * Ed25519, Cardano, Monero, sr25519, and Canton return "".
 *
 * Empty passphrase is the normal "no 25th word" case.
 * Returns empty String on failure.
 */
String derive_account_xpub(const wallet_generation_result& wallet,
                         const String& passphrase,
                         const hd_watch_coin& coin,
                         uint32_t account);



/**
 * BIP39 seed. Passphrase must be printable ASCII (no NFKD). Empty passphrase
 * is the BIP39 default. Writes 64 bytes to seed_out.
 */
bool hd_mnemonic_to_seed(const char* mnemonic, const char* passphrase, uint8_t seed_out[64]);

/**
 * BIP32 node at path ("m", "m/84'/0'/0'", "m/0'/1") serialized with version.
 * Hardened and normal steps are both accepted. version is the 4-byte SLIP-0132
 * prefix (xpub, ypub, zpub).
 * Returns an empty String on failure.
 */
String hd_derive_xpub(const uint8_t* seed, size_t seed_len, const char* path, const uint8_t version[4]);

#endif  // ARDUINO
