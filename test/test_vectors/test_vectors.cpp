// Runs the vendored official vectors in official_vectors.inc.
// BIP39 English seeds use passphrase TREZOR (Trezor vectors.json / BIP-0039).
// BIP32 vectors 1-4 are from BIP-0032. SLIP-0132 account keys use an empty passphrase.

#include <Arduino.h>
#include <unity.h>
#include <string.h>

#include "bip39/bip39_generator.h"
#include "coins/hd_coins.h"
#include "../test_screen.h"

#include "official_vectors.inc"

static bool hex_to_bytes(const char* hex, uint8_t* out, size_t out_len) {
  if (hex == nullptr || strlen(hex) != out_len * 2) return false;
  for (size_t i = 0; i < out_len; ++i) {
    unsigned value = 0;
    if (sscanf(hex + (i * 2), "%02x", &value) != 1) return false;
    out[i] = static_cast<uint8_t>(value);
  }
  return true;
}

static bool seed_equals(const uint8_t seed[64], const char* hex) {
  uint8_t expected[64];
  if (!hex_to_bytes(hex, expected, sizeof(expected))) return false;
  return memcmp(seed, expected, sizeof(expected)) == 0;
}

static String join_mnemonic(const wallet_generation_result& wallet) {
  String phrase;
  for (int i = 0; i < 24; ++i) {
    if (i > 0) phrase += ' ';
    phrase += wallet.mnemonic_24_words[i];
  }
  return phrase;
}

static void test_bip39_official_vectors(void) {
  const int count = static_cast<int>(sizeof(kBip39English) / sizeof(kBip39English[0]));
  TEST_ASSERT_GREATER_THAN(0, count);
  for (int i = 0; i < count; ++i) {
    const Bip39Vector& vector = kBip39English[i];
    uint8_t seed[64];
    TEST_ASSERT_TRUE_MESSAGE(hd_mnemonic_to_seed(vector.mnemonic, "TREZOR", seed), vector.mnemonic);
    TEST_ASSERT_TRUE_MESSAGE(seed_equals(seed, vector.seed), vector.mnemonic);

    if (strlen(vector.entropy) != 64) continue;
    binary_256 entropy = {};
    TEST_ASSERT_TRUE(hex_to_bytes(vector.entropy, entropy.data, sizeof(entropy.data)));
    const wallet_generation_result wallet = generate_wallet_from_entropy(entropy, BIP39_EN);
    TEST_ASSERT_TRUE_MESSAGE(wallet.success, vector.entropy);
    const String phrase = join_mnemonic(wallet);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(vector.mnemonic, phrase.c_str(), vector.entropy);
    TEST_ASSERT_TRUE(bip39_checksum_valid_mnemonic(phrase, BIP39_EN));
  }
}

static void test_bip32_official_vectors(void) {
  const uint8_t xpub_version[4] = {0x04, 0x88, 0xB2, 0x1E};
  const uint8_t xprv_version[4] = {0x04, 0x88, 0xAD, 0xE4};
  const int count = static_cast<int>(sizeof(kBip32) / sizeof(kBip32[0]));
  TEST_ASSERT_EQUAL(4, count);
  for (int i = 0; i < count; ++i) {
    const Bip32Vector& vector = kBip32[i];
    uint8_t seed[64];
    const size_t seed_len = strlen(vector.seed) / 2;
    TEST_ASSERT_TRUE(seed_len == 16 || seed_len == 32 || seed_len == 64);
    TEST_ASSERT_TRUE(hex_to_bytes(vector.seed, seed, seed_len));
    for (int chain = 0; chain < vector.count; ++chain) {
      const Bip32Chain& item = vector.chains[chain];
      char label[32];
      snprintf(label, sizeof(label), "bip32 %d %s", vector.id, item.path);
      TEST_ASSERT_EQUAL_STRING_MESSAGE(
          item.xpub, hd_derive_xpub(seed, seed_len, item.path, xpub_version).c_str(), label);
    }
  }
}

static void test_slip0132_official_vectors(void) {
  uint8_t seed[64];
  TEST_ASSERT_TRUE(hd_mnemonic_to_seed(kSlipMnemonic, "", seed));
  const int count = static_cast<int>(sizeof(kSlip) / sizeof(kSlip[0]));
  TEST_ASSERT_EQUAL(3, count);
  for (int i = 0; i < count; ++i) {
    uint8_t version[4];
    TEST_ASSERT_TRUE(hex_to_bytes(kSlip[i].version, version, sizeof(version)));
    TEST_ASSERT_EQUAL_STRING_MESSAGE(
        kSlip[i].xpub,
        hd_derive_xpub(seed, sizeof(seed), kSlip[i].path, version).c_str(),
        kSlip[i].path);
  }
}

void setup() {
  delay(2000);
  test_show_name("test_vectors.cpp");
  UNITY_BEGIN();

  RUN_TEST(test_bip39_official_vectors);
  test_show_result("bip39 official vectors", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_bip32_official_vectors);
  test_show_result("bip32 official vectors", Unity.CurrentTestFailed == 0);
  
  RUN_TEST(test_slip0132_official_vectors);
  test_show_result("slip0132 official vectors", Unity.CurrentTestFailed == 0);

  UNITY_END();
}

void loop() {}
