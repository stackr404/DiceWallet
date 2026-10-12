
#pragma once

#include <stdint.h>
#include "bip39/bip39_wordlist.h"

// Confirms the 24 displayed words, one at a time.
// Four buttons: the correct word plus three random BIP39 words.
// The correct button position is chosen with the ESP32 TRNG.
// On success, Continue-equivalent is ui_main_menu_show().
void ui_new_wallet_verify_seed_show(const char *const words[24],
                                    const uint16_t indexes[24],
                                    bip39_language lang);
void ui_new_wallet_verify_seed_wipe(void);
