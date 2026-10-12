#include <stdio.h>
#include <string.h>
#include <lvgl.h>
#include "bip39/bip39_generator.h"
#include "bip39/bip39_wordlist.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_import_wallet_words.h"
#include "ui/screens/ui_import_wallet_words_24th_word.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static const char *s_words[8];
static int s_count = 0;
static int s_index = 0;
static lv_obj_t *s_name = nullptr;

static void show_word(void) {
  if (s_name == nullptr) return;
  lv_label_set_text(s_name, s_count > 0 ? s_words[s_index] : "");
}

static void on_prev(lv_event_t *event) {
  (void)event;
  if (s_count < 1) return;
  s_index = (s_index == 0) ? s_count - 1 : s_index - 1;
  show_word();
}

static void on_next(lv_event_t *event) {
  (void)event;
  if (s_count < 1) return;
  s_index++;
  if (s_index >= s_count) s_index = 0;
  show_word();
}

static void on_select(lv_event_t *event) {
  (void)event;
  if (s_count < 1 || s_words[s_index] == nullptr) return;
  const char *word = s_words[s_index];
  ui_import_wallet_words_24th_word_wipe();
  ui_import_wallet_choose_word(word);
}

static void on_back(lv_event_t *event) {
  (void)event;
  ui_import_wallet_words_24th_word_wipe();
  ui_import_wallet_words_resume();
}

static lv_obj_t *make_button(lv_obj_t *parent, const char *text, int width, int y, lv_event_cb_t handler) {
  lv_obj_t *button = lv_button_create(parent);
  lv_obj_set_size(button, width, 40);
  lv_obj_align(button, LV_ALIGN_TOP_MID, 0, y);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(button, 8, 0);
  lv_obj_set_style_border_width(button, 0, 0);
  lv_obj_add_event_cb(button, handler, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);
  return button;
}

void ui_import_wallet_words_24th_word_show(void) {
  s_count = 0;
  s_index = 0;
  s_name = nullptr;
  for (int i = 0; i < 8; ++i) s_words[i] = nullptr;

  int indexes[23];
  for (int i = 0; i < 23; ++i) {
    indexes[i] = bip39_word_index(ui_import_wallet_chosen(i), BIP39_EN);
  }
  int final_index[8];
  const int n = bip39_valid_final_words(indexes, final_index, BIP39_EN);
  const char *const *words = bip39_words(BIP39_EN);
  if (n == 8 && words != nullptr) {
    for (int i = 0; i < 8; ++i) {
      if (final_index[i] < 0 || final_index[i] >= bip39_word_count()) continue;
      s_words[s_count++] = words[final_index[i]];
    }
  }

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Select 24th Word"));

  s_name = lv_label_create(screen);
  lv_obj_set_style_text_font(s_name, UI_FONT(22), 0);
  lv_obj_set_style_text_color(s_name, lv_color_hex(UI_COLOR_TITLE), 0);
  lv_obj_align(s_name, LV_ALIGN_TOP_MID, 0, 80);
  show_word();

  lv_obj_t *prev = lv_button_create(screen);
  lv_obj_set_size(prev, 70, 40);
  lv_obj_align(prev, LV_ALIGN_TOP_MID, -55, 130);
  lv_obj_set_style_bg_color(prev, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(prev, 8, 0);
  lv_obj_set_style_border_width(prev, 0, 0);
  lv_obj_add_event_cb(prev, on_prev, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *prev_label = lv_label_create(prev);
  lv_label_set_text(prev_label, TR("<"));
  lv_obj_set_style_text_font(prev_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(prev_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(prev_label);

  lv_obj_t *next = lv_button_create(screen);
  lv_obj_set_size(next, 70, 40);
  lv_obj_align(next, LV_ALIGN_TOP_MID, 55, 130);
  lv_obj_set_style_bg_color(next, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(next, 8, 0);
  lv_obj_set_style_border_width(next, 0, 0);
  lv_obj_add_event_cb(next, on_next, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *next_label = lv_label_create(next);
  lv_label_set_text(next_label, TR(">"));
  lv_obj_set_style_text_font(next_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(next_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(next_label);

  make_button(screen, TR("Select"), 200, 190, on_select);
  make_button(screen, TR("Back"), 200, 250, on_back);

  ui_screen_replace(screen);
}

void ui_import_wallet_words_24th_word_wipe(void) {
  for (int i = 0; i < 8; ++i) s_words[i] = nullptr;
  s_count = 0;
  s_index = 0;
  s_name = nullptr;
}