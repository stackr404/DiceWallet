#pragma once

#include "bip39/bip39_generator.h"

void wallet_clear_rolls(void);
void wallet_add_roll(int face);
int wallet_roll_count(void);
const int *wallet_rolls(void);

void wallet_set_generation(const wallet_generation_result& result);
const wallet_generation_result& wallet_generation(void);
bool wallet_has_generation(void);
void wallet_clear_generation(void);

// Zero rolls, word indexes, and the generation flag. Call on exit and finish.
void wallet_wipe_secrets(void);
