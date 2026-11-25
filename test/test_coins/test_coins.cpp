#include <Arduino.h>
#include <unity.h>
#include "../test_screen.h"
#include "coins/hd_coins.h"
#include "../data/vectors.h"

static bool phrase_to_wallet(const char* phrase, wallet_generation_result* out) {
  int idxs[24];
  int n = 0;
  const char* p = phrase;
  while (*p && n < 24) {
    while (*p == ' ') p++;
    if (!*p) break;
    char word[16];
    size_t len = 0;
    while (*p && *p != ' ' && len + 1 < sizeof(word)) word[len++] = *p++;
    word[len] = '\0';
    const int idx = bip39_word_index(word, BIP39_EN);
    if (idx < 0) return false;
    idxs[n++] = idx;
  }
  if (n != 24) return false;
  const char* const* words = bip39_words(BIP39_EN);
  *out = {};
  out->success = true;
  out->lang = BIP39_EN;
  for (int i = 0; i < 24; i++) {
    out->word_indexes[i] = static_cast<uint16_t>(idxs[i]);
    out->mnemonic_24_words[i] = words[idxs[i]];
  }
  return true;
}

static const hd_watch_coin* coin_by_code(const char* code) {
  if (strcmp(code, "BTC") == 0) return &hd_coin_BTC;
  if (strcmp(code, "ETH") == 0) return &hd_coin_ETH;
  if (strcmp(code, "XRP") == 0) return &hd_coin_XRP;
  return nullptr;
}

static void test_account_xpub_vectors(void) {
  for (int i = 0; i < kAccountXpubVectorCount; i++) {
    const AccountXpubVector& v = kAccountXpubVectors[i];
    const hd_watch_coin* coin = coin_by_code(v.coin);
    TEST_ASSERT_NOT_NULL_MESSAGE(coin, v.id);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(v.path, coin->note, v.id);

    wallet_generation_result wallet{};
    TEST_ASSERT_TRUE_MESSAGE(phrase_to_wallet(v.mnemonic, &wallet), v.id);
    TEST_ASSERT_TRUE(bip39_checksum_valid_mnemonic(String(v.mnemonic), BIP39_EN));

    const String derived = derive_account_xpub(wallet, v.passhrase, *coin, 0);
    TEST_ASSERT_GREATER_THAN_MESSAGE(0, derived.length(), v.id);
    TEST_ASSERT_EQUAL_STRING_MESSAGE(v.xpub, derived.c_str(), v.id);
  }
}

static void test_empty_wallet_rejected(void) {
  wallet_generation_result empty{};
  const String missing = derive_account_xpub(empty, String(""), hd_coin_BTC, 0);
  TEST_ASSERT_EQUAL(0, missing.length());
}

static void test_non_ascii_passphrase_rejected(void) {
  binary_256 zeros{};
  const wallet_generation_result w = generate_wallet_from_entropy(zeros, BIP39_EN);
  const String bad = derive_account_xpub(w, String("päss"), hd_coin_BTC, 0);
  TEST_ASSERT_EQUAL(0, bad.length());
}

static void test_unsupported_algo_rejected(void) {
  binary_256 zeros{};
  const wallet_generation_result w = generate_wallet_from_entropy(zeros, BIP39_EN);
  hd_watch_coin unsupported = hd_coin_BTC;
  unsupported.algo = HD_ALGO_SLIP10_ED25519;
  unsupported.this_firmware = false;
  const String xpub = derive_account_xpub(w, String(""), unsupported, 0);
  TEST_ASSERT_EQUAL(0, xpub.length());
}

// Expected values computed independently (Python: PBKDF2, HMAC-SHA512,
// secp256k1, HASH160). A different passphrase must give a different fingerprint.
static void test_master_fingerprint(void) {
  struct FpCase { const char* phrase; const char* pass; uint8_t fp[4]; };
  static const FpCase cases[] = {
    {kAbandonPhrase, "", {0x54, 0x36, 0xd7, 0x24}},
    {kDiceOnesPhrase, "", {0xac, 0x0e, 0x5f, 0x0a}},
    {kDiceOnesPhrase, "MyPassphrase", {0xd9, 0xa1, 0xf2, 0x3f}},
  };
  for (const FpCase& c : cases) {
    wallet_generation_result wallet{};
    TEST_ASSERT_TRUE(phrase_to_wallet(c.phrase, &wallet));
    uint8_t fp[4] = {0xff, 0xff, 0xff, 0xff};
    const String xpub = derive_account_xpub(wallet, String(c.pass), hd_coin_BTC, 0, fp);
    TEST_ASSERT_GREATER_THAN(0, xpub.length());
    TEST_ASSERT_EQUAL_HEX8_ARRAY(c.fp, fp, 4);
  }
}

void setup() {
  delay(2000);
  test_show_name("test_coins.cpp");
  UNITY_BEGIN();

  RUN_TEST(test_account_xpub_vectors);
  test_show_result("xpub vectors", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_empty_wallet_rejected);
  test_show_result("empty wallet rejected", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_non_ascii_passphrase_rejected);
  test_show_result("non ascii passphrse rejected", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_unsupported_algo_rejected);
  test_show_result("unsupported algo rejected", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_master_fingerprint);
  test_show_result("master fingerprint", Unity.CurrentTestFailed == 0);

  UNITY_END();
}

void loop() {}
