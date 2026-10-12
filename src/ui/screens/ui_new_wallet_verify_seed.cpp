#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <esp_random.h>
#include "app/secure_mem.h"
#include "bip39/bip39_wordlist.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_wallet_display_seed.h"
#include "ui/screens/ui_wallet_passphrase.h"
#include "ui/screens/ui_wallet_view_public_keys.h"
#include "ui/screens/ui_settings_advanced.h"
#include "ui/screens/ui_new_wallet_verify_seed.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static const int kChoices = 4;
static const int kMaxMistakes = 3;

static const char *s_words[24];
static uint16_t s_indexes[24];
static bip39_language s_lang = BIP39_EN;
static int s_step = 0;
static int s_mistakes = 0;
static int s_correct_slot = 0;
static lv_obj_t *s_prompt = nullptr;
static lv_obj_t *s_mistakes_label = nullptr;
static lv_obj_t *s_buttons[kChoices];
static lv_obj_t *s_button_labels[kChoices];

static uint32_t trng_below(uint32_t n) {
  if (n <= 1) return 0;
  const uint32_t limit = (0xFFFFFFFFu / n) * n;
  uint32_t value = 0;
  do {
    value = esp_random();
  } while (value >= limit);
  return value % n;
}

static void wipe_label(lv_obj_t *label) {
  if (label == nullptr) return;
  char *text = lv_label_get_text(label);
  if (text != nullptr) secure_wipe(text, strlen(text));
  lv_label_set_text(label, "        ");
}

static void wipe_verify_copies(void) {
  for (int slot = 0; slot < kChoices; slot++) wipe_label(s_button_labels[slot]);
  wipe_label(s_prompt);
  for (int i = 0; i < 24; i++) s_words[i] = nullptr;
  secure_wipe(s_indexes, sizeof(s_indexes));
  s_correct_slot = 0;
  s_step = 0;
}

static void return_to_seed(void) {
  const char *words[24];
  uint16_t indexes[24];
  for (int i = 0; i < 24; i++) {
    words[i] = s_words[i];
    indexes[i] = s_indexes[i];
  }
  wipe_verify_copies();
  ui_wallet_display_seed_show(false);
  secure_wipe(indexes, sizeof(indexes));
  for (int i = 0; i < 24; i++) words[i] = nullptr;
}

static void update_mistakes_label(void) {
  char text[24];
  snprintf(text, sizeof(text), TR("Mistakes %d of %d"), s_mistakes, kMaxMistakes);
  lv_label_set_text(s_mistakes_label, text);
  memset(text, 0, sizeof(text));
}

static void fill_choices(void) {
  const char *const *list = bip39_words(s_lang);
  const int count = bip39_word_count();
  const char *correct = s_words[s_step];
  s_correct_slot = (int)trng_below((uint32_t)kChoices);

  const char *choices[kChoices] = {};
  choices[s_correct_slot] = correct;

  for (int slot = 0; slot < kChoices; slot++) {
    if (slot == s_correct_slot) continue;
    const char *pick = nullptr;
    do {
      pick = list[trng_below((uint32_t)count)];
      bool used = strcmp(pick, correct) == 0;
      for (int prev = 0; prev < slot && !used; prev++) {
        if (choices[prev] != nullptr && strcmp(choices[prev], pick) == 0) used = true;
      }
      if (!used) break;
    } while (true);
    choices[slot] = pick;
  }

  for (int slot = 0; slot < kChoices; slot++) {
    lv_label_set_text(s_button_labels[slot], choices[slot]);
    choices[slot] = nullptr;
  }
}

static void show_step(void) {
  char title[32];
  snprintf(title, sizeof(title), TR("Confirm word %d of 24"), s_step + 1);
  lv_label_set_text(s_prompt, title);
  memset(title, 0, sizeof(title));
  fill_choices();
}

static void on_choice(lv_event_t *event) {
  if (lv_event_get_code(event) != LV_EVENT_CLICKED) return;
  const int slot = (int)(intptr_t)lv_event_get_user_data(event);
  if (slot != s_correct_slot) {
    s_mistakes++;
    update_mistakes_label();
    if (s_mistakes >= kMaxMistakes) return_to_seed();
    return;
  }
  s_step++;
  if (s_step >= 24) {
    wipe_verify_copies();
    if (ui_settings_advanced_enabled()) ui_wallet_passphrase_show();
    else ui_wallet_view_public_keys_show();
    return;
  }
  show_step();
}

static void on_view_seed(lv_event_t *event) {
  (void)event;
  return_to_seed();
}

void ui_new_wallet_verify_seed_show(const char *const words[24],
                                    const uint16_t indexes[24],
                                    bip39_language lang) {
  s_lang = lang;
  s_step = 0;
  s_mistakes = 0;
  for (int i = 0; i < 24; i++) {
    s_words[i] = words != nullptr ? words[i] : "";
    s_indexes[i] = indexes != nullptr ? indexes[i] : 0;
  }

  lv_obj_t *screen = ui_make_screen();

  s_prompt = ui_make_title(screen, TR("Word 1 of 24"));

  for (int slot = 0; slot < kChoices; slot++) {
    s_buttons[slot] = lv_button_create(screen);
    lv_obj_set_size(s_buttons[slot], 200, 32);
    lv_obj_align(s_buttons[slot], LV_ALIGN_TOP_MID, 0, 40 + slot * 38);
    lv_obj_set_style_bg_color(s_buttons[slot], lv_color_hex(UI_COLOR_BUTTON), 0);
    lv_obj_set_style_radius(s_buttons[slot], 8, 0);
    lv_obj_set_style_border_width(s_buttons[slot], 0, 0);
    lv_obj_add_event_cb(s_buttons[slot], on_choice, LV_EVENT_CLICKED, (void *)(intptr_t)slot);

    s_button_labels[slot] = lv_label_create(s_buttons[slot]);
    lv_label_set_text(s_button_labels[slot], "");
    lv_obj_set_style_text_font(s_button_labels[slot], UI_FONT(14), 0);
    lv_obj_set_style_text_color(s_button_labels[slot], lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_center(s_button_labels[slot]);
  }

  s_mistakes_label = lv_label_create(screen);
  lv_label_set_text(s_mistakes_label, TR("Mistakes 0 of 3"));
  lv_obj_set_style_text_font(s_mistakes_label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_mistakes_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(s_mistakes_label, LV_ALIGN_TOP_MID, 0, 196);

  lv_obj_t *back = lv_button_create(screen);
  lv_obj_set_size(back, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(back, LV_ALIGN_BOTTOM_MID, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(back, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(back, 8, 0);
  lv_obj_set_style_border_width(back, 0, 0);
  lv_obj_add_event_cb(back, on_view_seed, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *back_label = lv_label_create(back);
  lv_label_set_text(back_label, TR("View Seed"));
  lv_obj_set_style_text_font(back_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(back_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(back_label);

  show_step();
  ui_screen_replace(screen);
}
void ui_new_wallet_verify_seed_wipe(void) {
  wipe_verify_copies();
  s_mistakes = 0;
  s_lang = BIP39_EN;
}
