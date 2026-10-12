#include "bip39/bip39_wordlist.h"


const char *const *bip39_words(bip39_language language) {
  switch (language) {
    case BIP39_EN:
    default:            return bip39_wordlist_en();
  }
}


int bip39_word_count(void) { return 2048; }
