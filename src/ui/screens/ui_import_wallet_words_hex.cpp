#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>
#include <lvgl.h>
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "bip39/bip39_generator.h"
#include "bip39/bip39_wordlist.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_import_wallet_method.h"
#include "ui/screens/ui_wallet_display_seed.h"
#include "ui/screens/ui_import_wallet_words_hex.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static int s_word = 0;
static char s_digits[4];
static int s_len = 0;
static const char *s_chosen[24];
static int s_indexes[24];

static lv_obj_t *s_progress = nullptr;
static lv_obj_t *s_box = nullptr;
static lv_obj_t *s_hint = nullptr;

static const char *word_for_index(int index) {
  if (index < 0 || index >= bip39_word_count()) return nullptr;
  return bip39_words(BIP39_EN)[index];
}

static bool parse_index(long *out) {
  if (s_len == 0) return false;
  char *end = nullptr;
  const long value = strtol(s_digits, &end, 16);
  if (end == s_digits || *end != '\0' || value < 0 || value > 0x7FF) return false;
  *out = value;
  return true;
}

static void refresh(void) {
  char line[48];
  snprintf(line, sizeof(line), TR("Word Index %d of 24"), s_word + 1);
  lv_label_set_text(s_progress, line);
  lv_label_set_text(s_box, s_len > 0 ? s_digits : TR("_"));

  if (s_len == 0) {
    lv_label_set_text(s_hint, TR("Enter word index"));
    return;
  }
  long value = 0;
  if (!parse_index(&value)) {
    lv_label_set_text(s_hint, TR("Invalid index"));
    return;
  }
  const char *word = word_for_index(static_cast<int>(value));
  snprintf(line, sizeof(line), TR("Word: %s"), word != nullptr ? word : "");
  lv_label_set_text(s_hint, line);
}

static void clear_digits(void) {
  s_len = 0;
  s_digits[0] = '\0';
}

static void finish_import(void) {
  wallet_generation_result result = {};
  result.lang = BIP39_EN;
  result.success = bip39_checksum_valid_indices(s_indexes, 24, BIP39_EN);
  for (int i = 0; i < 24; i++) {
    result.mnemonic_24_words[i] = s_chosen[i];
    result.word_indexes[i] = static_cast<uint16_t>(s_indexes[i]);
  }
  if (!result.success) {
    // clear_digits();
    // refresh();
    // return;
    lv_label_set_text(s_hint, TR("Incorrect 24th index"));
    return;    
  }
  wallet_set_generation(result);
  ui_wallet_display_seed_show(true);
}

static void accept_index(void) {
  long value = 0;
  if (!parse_index(&value)) return;
  const char *word = word_for_index(static_cast<int>(value));
  if (word == nullptr) return;
  s_chosen[s_word] = word;
  s_indexes[s_word] = static_cast<int>(value);
  clear_digits();
  if (s_word < 23) {
    s_word++;
    refresh();
    return;
  }
  finish_import();
}

static void on_digit(lv_event_t *event) {
  if (s_len >= 3) return;
  const char digit = static_cast<char>(reinterpret_cast<intptr_t>(lv_event_get_user_data(event)));
  s_digits[s_len++] = digit;
  s_digits[s_len] = '\0';
  refresh();
}

static void on_delete(lv_event_t *event) {
  (void)event;
  if (s_len <= 0) return;
  s_digits[--s_len] = '\0';
  refresh();
}

static void on_ok(lv_event_t *event) {
  (void)event;
  accept_index();
}

static void on_back(lv_event_t *event) {
  (void)event;
  device_wipe_secrets();
  ui_import_wallet_method_show();
  device_scrub_residue();
}

static lv_obj_t *add_key(lv_obj_t *parent, const char *text, int x, int y, int w, int h, lv_event_cb_t handler, void *data) {
  lv_obj_t *button = lv_button_create(parent);
  lv_obj_set_size(button, w, h);
  lv_obj_set_pos(button, x, y);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
  lv_obj_set_style_radius(button, 6, 0);
  lv_obj_set_style_border_width(button, 0, 0);
  lv_obj_set_style_pad_all(button, 0, 0);
  lv_obj_add_event_cb(button, handler, LV_EVENT_CLICKED, data);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);
  return button;
}

void ui_import_wallet_words_hex_show(void) {
  s_word = 0;
  clear_digits();
  for (int i = 0; i < 24; i++) {
    s_chosen[i] = nullptr;
    s_indexes[i] = 0;
  }

  lv_obj_t *screen = ui_make_screen();
  
  ui_make_title(screen, TR("Import Wallet"));

  s_progress = lv_label_create(screen);
  lv_obj_set_style_text_font(s_progress, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_progress, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(s_progress, LV_ALIGN_TOP_MID, 0, 50);

  s_box = lv_label_create(screen);
  lv_obj_set_style_text_font(s_box, UI_FONT(22), 0);
  lv_obj_set_style_text_color(s_box, lv_color_hex(UI_COLOR_TITLE), 0);
  lv_obj_align(s_box, LV_ALIGN_TOP_MID, 0, 69);

  s_hint = lv_label_create(screen);
  lv_obj_set_style_text_font(s_hint, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_hint, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(s_hint, LV_ALIGN_TOP_MID, 0, 96);

  const int key_w = 52;
  const int key_h = 27;
  const int gap = 6;
  const int origin_x = (240 - (key_w * 4 + gap * 3)) / 2;
  const int origin_y = 122;
 const char *labels[] = {
    "0", "1", "2", "3",
    "4", "5", "6", "7",
    "8", "9", "A", "B",
    "C", "D", "E", "F"
};
for (int i = 0; i < 16; i++) {
  const int col = i % 4;
  const int row = i / 4;
  add_key(screen, labels[i], origin_x + col * (key_w + gap), origin_y + row * (key_h + gap),
          key_w, key_h, on_digit, reinterpret_cast<void *>(static_cast<intptr_t>(labels[i][0])));
}
const int action_y = origin_y + 4 * (key_h + gap);
const int action_w = key_w * 2 + gap;
add_key(screen, TR("Del"), origin_x, action_y, action_w, key_h, on_delete, nullptr);
add_key(screen, TR("OK"), origin_x + action_w + gap, action_y, action_w, key_h, on_ok, nullptr);
add_key(screen, TR("Cancel"), origin_x, action_y + key_h + gap, key_w * 4 + gap * 3, key_h, on_back, nullptr);

  refresh();
  ui_screen_replace(screen);
}
void ui_import_wallet_words_hex_wipe(void) {
  secure_wipe(s_digits, sizeof(s_digits));
  secure_wipe(s_indexes, sizeof(s_indexes));
  s_len = 0;
  s_word = 0;
  for (int i = 0; i < 24; ++i) s_chosen[i] = nullptr;
}
