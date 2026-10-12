#include "app/wallet.h"

#include "ui/screens/ui_settings_advanced.h"
#include "dice/die_rolls.h"

#include <stddef.h>
#include <stdint.h>

// Volatile store so the compiler cannot delete the wipe.
static void secure_wipe(void *ptr, size_t len) {
  volatile uint8_t *p = static_cast<volatile uint8_t *>(ptr);
  while (len--) {
    *p++ = 0;
  }
}

static int rolls[k_max_die_rolls];
static int roll_count;
static wallet_generation_result s_generation = {};
static bool s_has_generation = false;

void wallet_clear_rolls(void) {
  secure_wipe(rolls, sizeof(rolls));
  roll_count = 0;
}

void wallet_add_roll(int face) {
  if (roll_count >= ui_settings_die_roll_count()) return;
  if (face < 1 || face > 6) return;
  rolls[roll_count] = face;
  roll_count++;
}

int wallet_roll_count(void) {
  return roll_count;
}

const int *wallet_rolls(void) {
  return rolls;
}

void wallet_set_generation(const wallet_generation_result& result) {
  s_generation = result;
  s_has_generation = result.success;
}

const wallet_generation_result& wallet_generation(void) {
  return s_generation;
}

bool wallet_has_generation(void) {
  return s_has_generation;
}

void wallet_clear_generation(void) {
  secure_wipe(&s_generation, sizeof(s_generation));
  for (int i = 0; i < 24; ++i) {
    s_generation.mnemonic_24_words[i] = nullptr;
    s_generation.word_indexes[i] = 0;
  }
  s_has_generation = false;
}

void wallet_wipe_secrets(void) {
  wallet_clear_rolls();
  wallet_clear_generation();
}
