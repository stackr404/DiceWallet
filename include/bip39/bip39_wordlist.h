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
/*const char *const *bip39_wordlist_es(void);
const char *const *bip39_wordlist_fr(void);
const char *const *bip39_wordlist_it(void);
const char *const *bip39_wordlist_pt(void);
const char *const *bip39_wordlist_cs(void);
const char *const *bip39_wordlist_ja(void);
const char *const *bip39_wordlist_ko(void);
const char *const *bip39_wordlist_zh_hans(void);
const char *const *bip39_wordlist_zh_hant(void);*/

const char *const *bip39_words(bip39_language language);
int bip39_word_count(void);