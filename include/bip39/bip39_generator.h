#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "bip39_wordlist.h"

struct binary_256 {
  uint8_t data[32];
};

// struct binary_256_result {
//   bool success;
//   int failAt;
//   binary_256 bits;
// };

// mnemonic_24_words[i] points into the language wordlist.
// The pointers stay valid for the life of the program.
// No heap copy of the phrase is made.
struct wallet_generation_result {
  bool success;
  const char *mnemonic_24_words[24];
  uint16_t word_indexes[24];
  bip39_language lang;
};

bool binary_256_from_die_rolls(binary_256 *out, const int *roll_sequence, int total_rolls);

wallet_generation_result generate_wallet_from_entropy(const binary_256& exactEntropy, bip39_language lang);
wallet_generation_result generate_wallet_from_die_rolls(const int *roll_sequence, int total_rolls, bip39_language lang);

String encode_base58_check(const uint8_t *input, size_t len);

int bip39_word_index(const char* word, bip39_language lang);
bool bip39_checksum_valid_indices(const int* word_indices, int count, bip39_language lang);
bool bip39_checksum_valid_mnemonic(const String& phrase, bip39_language lang);

int bip39_valid_final_words(const int* first_23_words, int out[8], bip39_language lang);