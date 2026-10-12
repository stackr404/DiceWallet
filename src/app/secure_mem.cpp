#include "app/secure_mem.h"

#include <stdint.h>
#include <string.h>
#include <esp_heap_caps.h>
#include <esp_random.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "app/wallet.h"
#include "drivers/drivers.h"
#include "ui/screens/ui_import_wallet_words.h"
#include "ui/screens/ui_import_wallet_words_bin.h"
#include "ui/screens/ui_import_wallet_words_hex.h"
#include "ui/screens/ui_import_wallet_words_index.h"
#include "ui/screens/ui_import_wallet_words_select_word.h"
#include "ui/screens/ui_import_wallet_words_24th_word.h"
#include "ui/screens/ui_new_wallet_verify_seed.h"
#include "ui/screens/ui_wallet_display_seed.h"
#include "ui/screens/ui_wallet_passphrase.h"

void secure_wipe(void *ptr, size_t len) {
  if (ptr == nullptr || len == 0) return;
  volatile uint8_t *p = static_cast<volatile uint8_t *>(ptr);

  // Zero pass
  for (size_t i = 0; i < len; i++) p[i] = 0;

  // Random pass
  for (size_t i = 0; i < len; i += 4) {
    uint32_t r = esp_random();
    size_t n = (i + 4 <= len) ? 4 : (len - i);
    for (size_t j = 0; j < n; j++) p[i + j] = static_cast<uint8_t>(r >> (j * 8));
  }

  // Final zero pass
  for (size_t i = 0; i < len; i++) p[i] = 0;
}

void secure_scrub_free_heap(void) {
  // Keep allocating until the largest free block is small.
  // Multiple passes catch fragments that become free later.
  for (int pass = 0; pass < 6; ++pass) {
    void *blocks[64];
    size_t sizes[64];
    size_t n = 0;

    for (;;) {
      const size_t largest = heap_caps_get_largest_free_block(MALLOC_CAP_8BIT);
      if (largest < 32 || n >= 64) break;

      size_t take = largest > 48 ? largest - 16 : largest / 2;
      if (take < 24) break;

      void *block = heap_caps_malloc(take, MALLOC_CAP_8BIT);
      if (block == nullptr) break;

      secure_wipe(block, take);
      blocks[n] = block;
      sizes[n] = take;
      n++;
    }

    for (size_t i = 0; i < n; ++i) {
      secure_wipe(blocks[i], sizes[i]);
      heap_caps_free(blocks[i]);
    }
  }
}

void secure_scrub_abandoned_stack(void) {
  // Wipe a larger local window. Caller frames must still wipe their own secrets.
  volatile uint8_t window[2048];
  for (size_t i = 0; i < sizeof(window); i++) window[i] = 0;
  (void)uxTaskGetStackHighWaterMark(nullptr);
}

void device_wipe_secrets(void) {
  wallet_wipe_secrets();
  ui_wallet_passphrase_clear();
  ui_import_wallet_words_wipe();
  ui_import_wallet_words_index_wipe();
  ui_import_wallet_words_hex_wipe();
  ui_import_wallet_words_bin_wipe();
  ui_import_wallet_words_select_word_wipe();
  ui_import_wallet_words_24th_word_wipe();
  ui_wallet_display_seed_wipe();
  ui_new_wallet_verify_seed_wipe();
}

void device_scrub_residue(void) {
  secure_scrub_abandoned_stack();
  drivers_wipe_framebuffer();
  drivers_blank_panel();
  secure_scrub_free_heap();
  secure_scrub_abandoned_stack();
}