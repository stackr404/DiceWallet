#pragma once

#include <stdint.h>

// words must hold 24 NUL-terminated BIP39 words.
// Continue returns to the main menu.
void ui_wallet_display_seed_show(bool imported = false);
void ui_wallet_display_seed_wipe(void);

