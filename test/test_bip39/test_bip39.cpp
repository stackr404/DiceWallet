#include <Arduino.h>
#include <unity.h>
#include "../test_screen.h"
#include "bip39/bip39_generator.h"
#include "../data/vectors.h"

// /**
//  * Calculates the Hamming Distance (total changed bits) between two 256-bit arrays.
//  * 
//  * @param array1 Pointer to the first 32-byte array.
//  * @param array2 Pointer to the second 32-byte array.
//  * @return The total number of bits that differ between the two arrays (0 to 256).
//  */
// static int count_changed_bits(const uint8_t *array1, const uint8_t *array2) {
//     int total_changed_bits = 0;

//     for (int i = 0; i < 32; i++) {
//         // XOR yields a 1-bit only where the bits in array1 and array2 differ
//         uint8_t xor_result = array1[i] ^ array2[i];

//         // __builtin_popcount is a compiler built-in that uses ultra-fast 
//         // hardware-level instructions (or optimized assembly) to count 1-bits.
//         total_changed_bits += __builtin_popcount(xor_result);
//     }

//     return total_changed_bits;
// }

static void join_phrase(const wallet_generation_result& w, char* out, size_t out_len) {
  size_t used = 0;
  out[0] = '\0';
  for (int i = 0; i < 24; i++) {
    const int n = snprintf(out + used, out_len - used, "%s%s", i ? " " : "",
                           w.mnemonic_24_words[i] ? w.mnemonic_24_words[i] : "");
    used += static_cast<size_t>(n);
  }
}

static void test_wordlist_bounds(void) {
  TEST_ASSERT_EQUAL(2048, bip39_word_count());
  TEST_ASSERT_NOT_NULL(bip39_words(BIP39_EN));
  TEST_ASSERT_EQUAL(0, bip39_word_index("abandon", BIP39_EN));
  TEST_ASSERT_EQUAL(2047, bip39_word_index("zoo", BIP39_EN));
  TEST_ASSERT_TRUE(bip39_word_index("notaword", BIP39_EN) < 0);
  TEST_ASSERT_TRUE(bip39_word_index(nullptr, BIP39_EN) < 0);
}

static void test_zero_entropy_abandon_phrase(void) {
  binary_256 zeros{};
  const wallet_generation_result w = generate_wallet_from_entropy(zeros, BIP39_EN);
  TEST_ASSERT_TRUE(w.success);
  char phrase[256];
  join_phrase(w, phrase, sizeof(phrase));
  TEST_ASSERT_EQUAL_STRING(kAbandonPhrase, phrase);
  TEST_ASSERT_EQUAL(0, w.word_indexes[0]);
  TEST_ASSERT_EQUAL(bip39_word_index("art", BIP39_EN), w.word_indexes[23]);
  TEST_ASSERT_TRUE(bip39_checksum_valid_mnemonic(String(phrase), BIP39_EN));
}

static void test_checksum_rejects_tamper(void) {
  binary_256 zeros{};
  const wallet_generation_result w = generate_wallet_from_entropy(zeros, BIP39_EN);
  int bad[24];
  for (int i = 0; i < 24; i++) bad[i] = w.word_indexes[i];
  bad[23] = (bad[23] + 1) % 2048;
  TEST_ASSERT_FALSE(bip39_checksum_valid_indices(bad, 24, BIP39_EN));
  TEST_ASSERT_FALSE(bip39_checksum_valid_mnemonic(String("abandon abandon"), BIP39_EN));
  TEST_ASSERT_FALSE(bip39_checksum_valid_indices(nullptr, 24, BIP39_EN));
}

static void test_dice_ones_phrase(void) {
  int rolls[100];
  for (int i = 0; i < 100; i++) rolls[i] = 1;
  const wallet_generation_result dice = generate_wallet_from_die_rolls(rolls, 100, BIP39_EN);
  TEST_ASSERT_TRUE(dice.success);
  char phrase[256];
  join_phrase(dice, phrase, sizeof(phrase));
  TEST_ASSERT_EQUAL_STRING(kDiceOnesPhrase, phrase);
  int idxs[24];
  for (int i = 0; i < 24; i++) idxs[i] = dice.word_indexes[i];
  TEST_ASSERT_TRUE(bip39_checksum_valid_indices(idxs, 24, BIP39_EN));
}

static void test_dice_extractor_rejects_bad_input(void) {
  int rolls[100];
  for (int i = 0; i < 100; i++) rolls[i] = 1;
  binary_256 extracted{};
  TEST_ASSERT_TRUE(binary_256_from_die_rolls(&extracted, rolls, 100));
  TEST_ASSERT_FALSE(binary_256_from_die_rolls(&extracted, rolls, 99));
  TEST_ASSERT_FALSE(binary_256_from_die_rolls(nullptr, rolls, 100));
  rolls[50] = 7;
  TEST_ASSERT_FALSE(binary_256_from_die_rolls(&extracted, rolls, 100));
  TEST_ASSERT_FALSE(generate_wallet_from_die_rolls(rolls, 100, BIP39_EN).success);
}

void setup() {
  delay(2000);
  test_show_name("test_bip39.cpp");
  UNITY_BEGIN();
  
  RUN_TEST(test_wordlist_bounds);
  test_show_result("wordlist bounds", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_zero_entropy_abandon_phrase);
  test_show_result("zero entropy", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_checksum_rejects_tamper);
  test_show_result("checksum rejects tamper", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_dice_ones_phrase);
  test_show_result("dice ones phrase", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_dice_extractor_rejects_bad_input);
  test_show_result("dice extractor bad input", Unity.CurrentTestFailed == 0);

  UNITY_END();
}

void loop() {}
