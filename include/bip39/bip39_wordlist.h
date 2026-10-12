#pragma once

enum bip39_language {
  BIP39_EN,
  BIP39_ES,
  BIP39_FR,
  BIP39_IT,
  BIP39_PT,
  BIP39_CS,
  BIP39_JA,
  BIP39_KO,
  BIP39_ZH_HANS,
  BIP39_ZH_HANT
};

const char *const *bip39_wordlist_en(void);

const char *const *bip39_words(bip39_language language);
int bip39_word_count(void);
