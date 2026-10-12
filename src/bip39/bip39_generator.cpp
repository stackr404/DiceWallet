#include "bip39/bip39_generator.h"
#include "dice/die_rolls.h"
#include "bip39/bip39_wordlist.h"

#include "mbedtls/sha256.h"
#include <string.h>

// Volatile store so the compiler cannot delete the wipe.
static void secure_wipe(void *ptr, size_t len) {
  volatile uint8_t *p = static_cast<volatile uint8_t *>(ptr);
  while (len--) *p++ = 0;
}

// k_min_die_rolls fair d6 rolls are ~258 bits. The settings screen allows k_min_die_rolls-k_max_die_rolls.
// Folding the entered faces with SHA-256 yields a 32-byte BIP39 sample.
// Domain separator + length stop a shorter sequence colliding with a prefix.
bool binary_256_from_die_rolls(binary_256 *out, const int *roll_sequence, int total_rolls) {
  if (out == nullptr || roll_sequence == nullptr || total_rolls < k_min_die_rolls || total_rolls > k_max_die_rolls) return false;

  uint8_t material[4 + k_max_die_rolls];
  material[0] = 'D';
  material[1] = '6';
  material[2] = 0x01;
  material[3] = static_cast<uint8_t>(total_rolls);
  for (int i = 0; i < total_rolls; ++i) {
    const int face = roll_sequence[i];
    if (face < 1 || face > 6) {
      secure_wipe(material, sizeof(material));
      return false;
    }
    material[4 + i] = static_cast<uint8_t>(face);
  }
  const size_t used = static_cast<size_t>(4 + total_rolls);
  mbedtls_sha256(material, used, out->data, 0);
  secure_wipe(material, sizeof(material));
  return true;
}

static wallet_generation_result emptyWallet(bip39_language lang) {
  wallet_generation_result result = {};
  result.success = false;
  result.lang = lang;
  for (int i = 0; i < 24; ++i) {
    result.mnemonic_24_words[i] = nullptr;
    result.word_indexes[i] = 0;
  }
  return result;
}

wallet_generation_result generate_wallet_from_die_rolls(const int *roll_sequence, int total_rolls, bip39_language lang) {
  binary_256 entropy;
  if (!binary_256_from_die_rolls(&entropy, roll_sequence, total_rolls)) return emptyWallet(lang);
  wallet_generation_result result = generate_wallet_from_entropy(entropy, lang);
  secure_wipe(entropy.data, sizeof(entropy.data));
  return result;
}

wallet_generation_result generate_wallet_from_entropy(const binary_256& exactEntropy, bip39_language lang) {
  wallet_generation_result result = emptyWallet(lang);
  const char *const *words = bip39_words(lang);
  if (words == nullptr) return result;

  uint8_t entropyHash[32];
  mbedtls_sha256(exactEntropy.data, 32, entropyHash, 0);
  const uint8_t checksum = entropyHash[0];

  uint8_t extendedEntropy[33];
  memcpy(extendedEntropy, exactEntropy.data, 32);
  extendedEntropy[32] = checksum;

  size_t bit_tracker = 0;
  for (int i = 0; i < 24; i++) {
    uint32_t current_accumulator = 0;
    const size_t byte_idx = bit_tracker / 8;
    const size_t bit_offset = bit_tracker % 8;

    current_accumulator |= ((uint32_t)extendedEntropy[byte_idx]) << 16;
    if (byte_idx + 1 < 33) current_accumulator |= ((uint32_t)extendedEntropy[byte_idx + 1]) << 8;
    if (byte_idx + 2 < 33) current_accumulator |= ((uint32_t)extendedEntropy[byte_idx + 2]);

    const uint16_t index = (uint16_t)((current_accumulator >> (24 - 11 - bit_offset)) & 0x7FF);
    result.mnemonic_24_words[i] = words[index];
    result.word_indexes[i] = index;
    bit_tracker += 11;
  }

  result.success = true;
  result.lang = lang;
  secure_wipe(entropyHash, sizeof(entropyHash));
  secure_wipe(extendedEntropy, sizeof(extendedEntropy));
  return result;
}

static int bip39WordCmp(const void* a, const void* b) {
  const char* key = static_cast<const char*>(a);
  const char* const* item = static_cast<const char* const*>(b);
  return strcmp(key, *item);
}

int bip39_word_index(const char* word, bip39_language lang) {
  const char *const *words = bip39_words(lang);
  if (!word || words == nullptr) return -1;
  const char* const* found = static_cast<const char* const*>(
      bsearch(word, words, (size_t)bip39_word_count(), sizeof(words[0]), bip39WordCmp));
  return found ? (int)(found - words) : -1;
}

bool bip39_checksum_valid_indices(const int* word_indices, int count, bip39_language lang) {
  (void)lang;
  if (!word_indices || count != 24) return false;
  uint8_t entropy[33];
  memset(entropy, 0, sizeof(entropy));
  int bit = 0;
  bool ok = false;
  for (int w = 0; w < 24; ++w) {
    const int idx = word_indices[w];
    if (idx < 0 || idx >= bip39_word_count()) goto done;
    for (int b = 10; b >= 0; --b) {
      const int byte = bit / 8;
      const int off = 7 - (bit % 8);
      if (idx & (1 << b)) entropy[byte] |= (uint8_t)(1u << off);
      bit++;
    }
  }
  {
    uint8_t hash[32];
    mbedtls_sha256(entropy, 32, hash, 0);
    ok = hash[0] == entropy[32];
    secure_wipe(hash, sizeof(hash));
  }
done:
  secure_wipe(entropy, sizeof(entropy));
  return ok;
}

bool bip39_checksum_valid_mnemonic(const String& phrase, bip39_language lang) {
  int idx[24];
  int n = 0;
  int start = 0;
  const int len = phrase.length();
  while (start < len && n < 24) {
    while (start < len && phrase[start] == ' ') start++;
    if (start >= len) break;
    int end = start;
    while (end < len && phrase[end] != ' ') end++;
    const String w = phrase.substring(start, end);
    const int found = bip39_word_index(w.c_str(), lang);
    if (found < 0) return false;
    idx[n++] = found;
    start = end;
  }
  if (n != 24) return false;
  while (start < len && phrase[start] == ' ') start++;
  if (start != len) return false;
  const bool ok = bip39_checksum_valid_indices(idx, 24, lang);
  secure_wipe(idx, sizeof(idx));
  return ok;
}

int bip39_valid_final_words(const int* first_23_words, int out[8], bip39_language lang) {
  (void)lang;
  if (first_23_words == nullptr || out == nullptr) return 0;
  for (int frag = 0; frag < 8; ++frag) {
    uint8_t entropy[32];
    memset(entropy, 0, sizeof(entropy));
    int bit = 0;
    bool bad = false;
    for (int w = 0; w < 23 && !bad; ++w) {
      const int idx = first_23_words[w];
      if (idx < 0 || idx >= bip39_word_count()) bad = true;
      for (int b = 10; b >= 0 && !bad; --b) {
        if (idx & (1 << b)) entropy[bit / 8] |= (uint8_t)(1u << (7 - (bit % 8)));
        bit++;
      }
    }
    if (!bad) {
      for (int b = 2; b >= 0; --b) {
        if (frag & (1 << b)) entropy[bit / 8] |= (uint8_t)(1u << (7 - (bit % 8)));
        bit++;
      }
    }
    if (bad || bit != 256) {
      secure_wipe(entropy, sizeof(entropy));
      return 0;
    }
    uint8_t hash[32];
    mbedtls_sha256(entropy, 32, hash, 0);
    out[frag] = (frag << 8) | hash[0];
    secure_wipe(hash, sizeof(hash));
    secure_wipe(entropy, sizeof(entropy));
  }
  return 8;
}