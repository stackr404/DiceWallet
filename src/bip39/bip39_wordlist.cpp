#include "bip39/bip39_wordlist.h"


const char *const *bip39_words(bip39_language language) {
  switch (language) {
    /*case BIP39_ES:      return bip39_wordlist_es();
    case BIP39_FR:      return bip39_wordlist_fr();
    case BIP39_IT:      return bip39_wordlist_it();
    case BIP39_PT:      return bip39_wordlist_pt();
    case BIP39_CS:      return bip39_wordlist_cs();
    case BIP39_JA:      return bip39_wordlist_ja();
    case BIP39_KO:      return bip39_wordlist_ko();
    case BIP39_ZH_HANS: return bip39_wordlist_zh_hans();
    case BIP39_ZH_HANT: return bip39_wordlist_zh_hant(); */
    case BIP39_EN:
    default:            return bip39_wordlist_en();
  }
}


int bip39_word_count(void) { return 2048; }