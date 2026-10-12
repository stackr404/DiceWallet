#include <stdio.h>
#include <string.h>
#include <lvgl.h>
#include "ui/screens/ui_import_wallet_words_bin.h"
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "bip39/bip39_generator.h"
#include "bip39/bip39_wordlist.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_import_wallet_method.h"
#include "ui/screens/ui_wallet_display_seed.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static const int kBits = 11;

static int s_word = 0;
static int s_bits[kBits];
static bool s_set[kBits];
static int s_cursor = 0;
static const char *s_chosen[24];
static int s_indexes[24];

static lv_obj_t *s_progress = nullptr;
static lv_obj_t *s_boxes[kBits];
static lv_obj_t *s_box_labels[kBits];
static lv_obj_t *s_carets[kBits];
static lv_obj_t *s_hint = nullptr;

static const char *word_for_index(int index) {
  if (index < 0 || index >= bip39_word_count()) return nullptr;
  return bip39_words(BIP39_EN)[index];
}

static bool complete(void) {
  for (int i = 0; i < kBits; i++) {
    if (!s_set[i]) return false;
  }
  return true;
}

static int index_value(void) {
  int value = 0;
  for (int i = 0; i < kBits; i++) value = (value << 1) | (s_bits[i] & 1);
  return value;
}

static void clear_bits(void) {
  s_cursor = 0;
  for (int i = 0; i < kBits; i++) {
    s_bits[i] = 0;
    s_set[i] = true;
  }
}

static void refresh(void) {
  char line[48];
  snprintf(line, sizeof(line), TR("Word Index %d of 24"), s_word + 1);
  lv_label_set_text(s_progress, line);

  for (int i = 0; i < kBits; i++) {
    char token[2] = {static_cast<char>('0' + s_bits[i]), '\0'};
    lv_label_set_text(s_box_labels[i], token);
    const bool on = s_bits[i] == 1;
    const bool active = i == s_cursor;
    lv_obj_set_style_bg_color(s_boxes[i], lv_color_hex(on ? UI_COLOR_TEXT : UI_COLOR_BG), 0);
    lv_obj_set_style_text_color(s_box_labels[i], lv_color_hex(on ? UI_COLOR_BG : UI_COLOR_TITLE), 0);
    lv_obj_set_style_border_width(s_boxes[i], active ? 2 : 1, 0);
    lv_obj_set_style_border_color(s_boxes[i], lv_color_hex(active ? UI_COLOR_TITLE : UI_COLOR_MUTED), 0);
    if (s_carets[i]) lv_label_set_text(s_carets[i], active ? "^" : "");
  }

  if (!complete()) {
    lv_label_set_text(s_hint, TR("Enter all bits"));
    return;
  }
  const char *word = word_for_index(index_value());
  snprintf(line, sizeof(line), TR("Word: %s"), word != nullptr ? word : "");
  lv_label_set_text(s_hint, line);
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
    // clear_bits();
    // refresh();
    // return;
    lv_label_set_text(s_hint, TR("Incorrect 24th index"));
    return;    
  }
  wallet_set_generation(result);
  ui_wallet_display_seed_show(true);
}

static void touch_cursor(void) {
  if (!s_set[s_cursor]) {
    s_bits[s_cursor] = 0;
    s_set[s_cursor] = true;
  }
}

static void on_left(lv_event_t *event) {
  (void)event;
  if (s_cursor > 0) s_cursor--;
  touch_cursor();
  refresh();
}

static void on_right(lv_event_t *event) {
  (void)event;
  if (s_cursor < kBits - 1) s_cursor++;
  touch_cursor();
  refresh();
}

static void on_flip(lv_event_t *event) {
  (void)event;
  touch_cursor();
  s_bits[s_cursor] = s_bits[s_cursor] ? 0 : 1;
  refresh();
}

static void on_ok(lv_event_t *event) {
  (void)event;
  if (!complete()) return;
  const int value = index_value();
  const char *word = word_for_index(value);
  if (word == nullptr) return;
  s_chosen[s_word] = word;
  s_indexes[s_word] = value;
  clear_bits();
  if (s_word < 23) {
    s_word++;
    refresh();
    return;
  }
  finish_import();
}

static void on_cancel(lv_event_t *event) {
  (void)event;
  device_wipe_secrets();
  ui_import_wallet_method_show();
  device_scrub_residue();
}

static lv_obj_t *add_key(lv_obj_t *parent, const char *text, int x, int y, int w, int h, lv_event_cb_t handler) {
  lv_obj_t *button = lv_button_create(parent);
  lv_obj_set_size(button, w, h);
  lv_obj_set_pos(button, x, y);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
  lv_obj_set_style_radius(button, 6, 0);
  lv_obj_set_style_border_width(button, 0, 0);
  lv_obj_set_style_pad_all(button, 0, 0);
  lv_obj_add_event_cb(button, handler, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);
  return button;
}

void ui_import_wallet_words_bin_show(void) {
  s_word = 0;
  clear_bits();
  for (int i = 0; i < 24; i++) {
    s_chosen[i] = nullptr;
    s_indexes[i] = 0;
  }

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Import Wallet"));

  s_progress = lv_label_create(screen);
  lv_obj_set_style_text_font(s_progress, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_progress, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(s_progress, LV_ALIGN_TOP_MID, 0, 45);

  const int box = 18;
  const int gap = 2;
  const int row_w = kBits * box + (kBits - 1) * gap;
  const int origin_x = (240 - row_w) / 2;
  const int origin_y = 72;
  for (int i = 0; i < kBits; i++) {
    s_boxes[i] = lv_obj_create(screen);
    lv_obj_set_size(s_boxes[i], box, 28);
    lv_obj_set_pos(s_boxes[i], origin_x + i * (box + gap), origin_y);
    lv_obj_set_style_bg_color(s_boxes[i], lv_color_hex(UI_COLOR_BG), 0);
    lv_obj_set_style_radius(s_boxes[i], 3, 0);
    lv_obj_set_style_border_width(s_boxes[i], 1, 0);
    lv_obj_set_style_border_color(s_boxes[i], lv_color_hex(UI_COLOR_MUTED), 0);
    lv_obj_set_style_pad_all(s_boxes[i], 0, 0);
    lv_obj_set_scrollbar_mode(s_boxes[i], LV_SCROLLBAR_MODE_OFF);
    s_box_labels[i] = lv_label_create(s_boxes[i]);
    lv_label_set_text(s_box_labels[i], "");
    lv_obj_set_style_text_font(s_box_labels[i], UI_FONT(14), 0);
    lv_obj_set_style_text_color(s_box_labels[i], lv_color_hex(UI_COLOR_TITLE), 0);
    lv_obj_center(s_box_labels[i]);
    s_carets[i] = lv_label_create(screen);
    lv_label_set_text(s_carets[i], "");
    lv_obj_set_style_text_font(s_carets[i], UI_FONT(14), 0);
    lv_obj_set_style_text_color(s_carets[i], lv_color_hex(UI_COLOR_TITLE), 0);
    lv_obj_align_to(s_carets[i], s_boxes[i], LV_ALIGN_OUT_BOTTOM_MID, -4, -2);
  }

  s_hint = lv_label_create(screen);
  lv_obj_set_style_text_font(s_hint, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_hint, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(s_hint, LV_ALIGN_TOP_MID, 0, 117);

  const int key_w = 70;
  const int key_h = 36;
  const int key_gap = 8;
  const int keys_w = key_w * 3 + key_gap * 2;
  const int key_x = (240 - keys_w) / 2;
  add_key(screen, TR("<"), key_x, 150, key_w, key_h, on_left);
  add_key(screen, TR("Flip"), key_x + key_w + key_gap, 150, key_w, key_h, on_flip);
  add_key(screen, TR(">"), key_x + 2 * (key_w + key_gap), 150, key_w, key_h, on_right);
  add_key(screen, TR("OK"), key_x, 196, keys_w, key_h, on_ok);
  add_key(screen, TR("Cancel"), key_x, 268, keys_w, key_h, on_cancel);

  refresh();
  ui_screen_replace(screen);
}
void ui_import_wallet_words_bin_wipe(void) {
  secure_wipe(s_bits, sizeof(s_bits));
  secure_wipe(s_set, sizeof(s_set));
  secure_wipe(s_indexes, sizeof(s_indexes));
  s_cursor = 0;
  s_word = 0;
  for (int i = 0; i < 24; ++i) s_chosen[i] = nullptr;
}
