#include <stdio.h>
#include <string.h>
#include <lvgl.h>
#include "bip39/bip39_wordlist.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_import_wallet_words.h"
#include "ui/screens/ui_import_wallet_words_select_word.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static const int kMaxChoices = 8;
static const char *s_choices[kMaxChoices];
static int s_choice_count = 0;

static bool prefix_match(const char *word, const char *prefix) {
  const size_t n = strlen(prefix);
  return n > 0 && strncmp(word, prefix, n) == 0;
}

static void on_choice(lv_event_t *event) {
  const int slot = static_cast<int>(reinterpret_cast<intptr_t>(lv_event_get_user_data(event)));
  if (slot < 0 || slot >= s_choice_count || s_choices[slot] == nullptr) return;
  ui_import_wallet_choose_word(s_choices[slot]);
}

static void on_back(lv_event_t *event) {
  (void)event;
  ui_import_wallet_words_back();
}

void ui_import_wallet_words_select_word_show(void) {
  const char *prefix = ui_import_wallet_typed_prefix();
  const char *const *words = bip39_words(BIP39_EN);
  s_choice_count = 0;
  for (int i = 0; i < bip39_word_count() && s_choice_count < kMaxChoices; i++) {
    if (prefix_match(words[i], prefix)) s_choices[s_choice_count++] = words[i];
  }

  lv_obj_t *screen = ui_make_screen();
  
  ui_make_title(screen, TR("Select Word"));

  char subtitle[48];
  snprintf(subtitle, sizeof(subtitle), TR("Word %d of 24: %s"), ui_import_wallet_word_number(), prefix);
  lv_obj_t *sub = lv_label_create(screen);
  lv_label_set_text(sub, subtitle);
  lv_obj_set_style_text_font(sub, UI_FONT(14), 0);
  lv_obj_set_style_text_color(sub, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(sub, LV_ALIGN_TOP_MID, 0, 45);

  for (int i = 0; i < s_choice_count; i++) {
    lv_obj_t *button = lv_button_create(screen);
    lv_obj_set_size(button, 200, 32);
    lv_obj_align(button, LV_ALIGN_TOP_MID, 0, 73 + i * 40);
    lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
    lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
    lv_obj_set_style_radius(button, 6, 0);
    lv_obj_set_style_border_width(button, 0, 0);
    lv_obj_add_event_cb(button, on_choice, LV_EVENT_CLICKED, reinterpret_cast<void *>(static_cast<intptr_t>(i)));

    lv_obj_t *label = lv_label_create(button);
    lv_label_set_text(label, s_choices[i]);
    lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
    lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_center(label);
  }

  lv_obj_t *back = lv_button_create(screen);
  lv_obj_set_size(back, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(back, UI_BUTTON_BOTTOM_ALIGN, 0, -10);
  lv_obj_set_style_bg_color(back, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_bg_color(back, lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
  lv_obj_set_style_radius(back, 6, 0);
  lv_obj_set_style_border_width(back, 0, 0);
  lv_obj_add_event_cb(back, on_back, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *back_label = lv_label_create(back);
  lv_label_set_text(back_label, TR("Back"));
  lv_obj_set_style_text_font(back_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(back_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(back_label);

  ui_screen_replace(screen);
}
void ui_import_wallet_words_select_word_wipe(void) {
  for (int i = 0; i < kMaxChoices; ++i) s_choices[i] = nullptr;
  s_choice_count = 0;
}
