#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <lvgl.h>
#include "bip39/bip39_wordlist.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_import_wallet_words.h"
#include "ui/screens/ui_import_wallet_method.h"
#include "ui/screens/ui_import_wallet_words_select_word.h"
#include "ui/screens/ui_import_wallet_words_24th_word.h"
#include "ui/screens/ui_wallet_display_seed.h"
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "bip39/bip39_generator.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static const char *kGroups[] = {
     "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};
static const int kMaxLetters = 8;
static const int kMaxSuggestions = 5;
static const uint32_t kCycleMs = 900;

static int s_word = 0;
static char s_letters[kMaxLetters + 1];
static int s_len = 0;
static bool s_editing = false;
static bool s_suppress_select = false;
static int s_last_group = -1;
static int s_cycle = 0;
static const char *s_chosen[24];
static lv_timer_t *s_cycle_timer = nullptr;

static lv_obj_t *s_progress = nullptr;
static lv_obj_t *s_pattern = nullptr;
static lv_obj_t *s_hint = nullptr;
static lv_obj_t *s_final_button = nullptr;
static lv_obj_t *s_pad = nullptr;
static lv_obj_t *s_slots[8];
static lv_obj_t *s_slot_labels[8];
static lv_obj_t *s_suggestions[kMaxSuggestions];
static lv_obj_t *s_suggestion_labels[kMaxSuggestions];
static const char *s_matches[kMaxSuggestions];

static void commit_letter(void) {
  s_editing = false;
  s_last_group = -1;
  s_cycle = 0;
}

static uint32_t s_last_key_ms = 0;
static void refresh(void);
static void ui_import_wallet_words_show_screen(void);
void ui_import_wallet_words_resume(void);
static void open_select_async(void *unused);

static bool s_words_screen_active = false;

static void cycle_timeout(lv_timer_t *timer) {
  (void)timer;
  if (!s_words_screen_active || !s_editing) return;
  if (millis() - s_last_key_ms < kCycleMs) return;
  commit_letter();
  refresh();
}

static void bump_cycle_timer(void) {
  s_last_key_ms = millis();
  if (s_cycle_timer == nullptr) {
    s_cycle_timer = lv_timer_create(cycle_timeout, 100, nullptr);
  } else {
    lv_timer_resume(s_cycle_timer);
  }
}

static bool word_matches(const char *word) {
  for (int i = 0; i < s_len; i++) {
    if (word[i] == '\0' || word[i] != (char)tolower((unsigned char)s_letters[i])) return false;
  }
  return true;
}

static int collect_matches(const char **out, int max_out, int *total) {
  const char *const *words = bip39_words(BIP39_EN);
  int found = 0;
  int count = 0;
  for (int i = 0; i < bip39_word_count(); i++) {
    if (s_len > 0 && !word_matches(words[i])) continue;
    if (s_len == 0) break;
    count++;
    if (found < max_out) out[found++] = words[i];
  }
  if (total) *total = count;
  return found;
}

static void open_select_async(void *unused) {
  (void)unused;
  if (!s_words_screen_active || s_editing || s_len < 1) return;
  s_words_screen_active = false;
  if (s_cycle_timer) lv_timer_pause(s_cycle_timer);
  ui_import_wallet_words_select_word_show();
}

static void refresh(void) {
  char line[40];
  snprintf(line, sizeof(line), TR("Word %d of 24"), s_word + 1);
  lv_label_set_text(s_progress, line);

  const int slots = s_len > 4 ? s_len : 4;
  const int current = s_editing && s_len > 0 ? s_len - 1 : s_len;
  for (int i = 0; i < 8; i++) {
    if (i >= slots) {
      lv_obj_set_hidden(s_slots[i], true);
      continue;
    }
    lv_obj_set_hidden(s_slots[i], false);
    char token[2] = {i < s_len ? s_letters[i] : '_', '\0'};
    lv_label_set_text(s_slot_labels[i], token);
    const bool active = i == current && current < 8;
    lv_obj_set_style_border_width(s_slots[i], active ? 2 : 1, 0);
    lv_obj_set_style_border_color(s_slots[i], lv_color_hex(active ? UI_COLOR_TITLE : UI_COLOR_MUTED), 0);
  }
  if (s_pattern) lv_obj_set_hidden(s_pattern, true);

  int total = 0;
  collect_matches(s_matches, kMaxSuggestions, &total);
  // const bool ready = !s_suppress_select && !s_editing && s_len >= 3 && total > 0 && total <= kMaxSuggestions;
  const bool ready = !s_suppress_select && !s_editing && s_len > 0 && total > 0 && total <= kMaxSuggestions;
  for (int i = 0; i < kMaxSuggestions; i++) {
    s_matches[i] = nullptr;
    if (s_suggestions[i]) lv_obj_set_hidden(s_suggestions[i], true);
  }
  if (s_pad) lv_obj_set_y(s_pad, 112);
  if (ready) {
    lv_label_set_text(s_hint, TR("Choose a word"));
    lv_obj_set_hidden(s_hint, false);
    lv_async_call(open_select_async, nullptr);
    if (s_final_button) lv_obj_set_hidden(s_final_button, true);
    return;
  } else if (s_len == 0) {
    lv_label_set_text(s_hint, TR("Type the word"));
    lv_obj_set_hidden(s_hint, false);
  } else if (s_len > 1 && total == 0) {
    lv_label_set_text(s_hint, TR("No matches."));
    lv_obj_set_hidden(s_hint, false);
  } else {
    snprintf(line, sizeof(line), TR("%s: %d matches. Keep typing."), s_letters, total);
    lv_label_set_text(s_hint, line);
    lv_obj_set_hidden(s_hint, false);
  }
  if (s_final_button) lv_obj_set_hidden(s_final_button, !(s_word == 23 && s_len == 0));
}

static void clear_letters(void) {
  s_len = 0;
  s_letters[0] = '\0';
  commit_letter();
  if (s_cycle_timer) lv_timer_pause(s_cycle_timer);
}

static void finish_import(void) {
  wallet_generation_result result = {};
  result.lang = BIP39_EN;
  int indexes[24];
  for (int i = 0; i < 24; i++) {
    result.mnemonic_24_words[i] = s_chosen[i];
    indexes[i] = bip39_word_index(s_chosen[i], BIP39_EN);
    result.word_indexes[i] = indexes[i] < 0 ? 0 : (uint16_t)indexes[i];
  }
  result.success = bip39_checksum_valid_indices(indexes, 24, BIP39_EN);
  if (!result.success) {
    ui_import_wallet_words_resume();
    return;
  }
  wallet_set_generation(result);
  ui_wallet_display_seed_show(true);
}

void ui_import_wallet_choose_word(const char *word) {
  if (s_word < 24) s_chosen[s_word] = word;
  clear_letters();
  if (s_word < 23) {
    s_word++;
    ui_import_wallet_words_resume();
    return;
  }
  finish_import();
}

const char *ui_import_wallet_typed_prefix(void) {
  return s_letters;
}

int ui_import_wallet_word_number(void) {
  return s_word + 1;
}

const char *ui_import_wallet_chosen(int index) {
  if (index < 0 || index >= 24) return nullptr;
  return s_chosen[index];
}

static void on_select_24th(lv_event_t *event) {
  (void)event;
  if (s_word != 23) return;
  s_words_screen_active = false;
  ui_import_wallet_words_24th_word_show();
}

static void on_group(lv_event_t *event) {
  const int group = static_cast<int>(reinterpret_cast<intptr_t>(lv_event_get_user_data(event)));
  const char *letters = kGroups[group];
  const int nletters = static_cast<int>(strlen(letters));

  if (s_editing && group == s_last_group && s_len > 0) {
    s_cycle = (s_cycle + 1) % nletters;
    s_letters[s_len - 1] = (char)tolower((unsigned char)letters[s_cycle]);
  } else if (s_len < kMaxLetters) {
    s_cycle = 0;
    s_letters[s_len++] = (char)tolower((unsigned char)letters[0]);
    s_letters[s_len] = '\0';
    s_editing = true;
    s_last_group = group;
  }
  s_suppress_select = false;
  bump_cycle_timer();
  refresh();
}

static void on_backspace(lv_event_t *event) {
  (void)event;
  if (s_len <= 0) return;
  s_letters[--s_len] = '\0';
  commit_letter();
  s_suppress_select = false;
  if (s_cycle_timer) lv_timer_pause(s_cycle_timer);
  refresh();
}

static void on_suggestion(lv_event_t *event) {
  const int slot = static_cast<int>(reinterpret_cast<intptr_t>(lv_event_get_user_data(event)));
  if (slot < 0 || slot >= kMaxSuggestions || s_matches[slot] == nullptr) return;
  ui_import_wallet_choose_word(s_matches[slot]);
}

static void on_back(lv_event_t *event) {
  (void)event;
  if (s_cycle_timer) {
    lv_timer_delete(s_cycle_timer);
    s_cycle_timer = nullptr;
  }
  s_words_screen_active = false;
  device_wipe_secrets();
  ui_import_wallet_method_show();
  device_scrub_residue();
}

static lv_obj_t *add_key(lv_obj_t *screen, const char *text, int x, int y, int w, int h, lv_event_cb_t handler, void *data) {
  lv_obj_t *button = lv_button_create(screen);
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

void ui_import_wallet_words_resume(void) {
  clear_letters();
  ui_import_wallet_words_show_screen();
}

void ui_import_wallet_words_back(void) {
  s_suppress_select = true;
  s_words_screen_active = true;
  if (s_cycle_timer) lv_timer_resume(s_cycle_timer);
  ui_import_wallet_words_show_screen();
}

void ui_import_wallet_words_show(void) {
  s_word = 0;
  clear_letters();
  for (int i = 0; i < 24; i++) s_chosen[i] = nullptr;
  ui_import_wallet_words_show_screen();
}

static void ui_import_wallet_words_show_screen(void) {
  
  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Import Wallet")); 

  s_progress = lv_label_create(screen);
  lv_label_set_text(s_progress, TR("Word 1 of 24"));
  lv_obj_set_style_text_font(s_progress, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_progress, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(s_progress, LV_ALIGN_TOP_MID, 0, 44);

  s_pattern = lv_label_create(screen);
  lv_obj_set_hidden(s_pattern, true);

  const int slot = 28;
  const int slot_gap = 8;
  const int slots_w = 4 * slot + 3 * slot_gap;
  const int slot_x = (240 - slots_w) / 2;
  const int slot_y = 65;
  for (int i = 0; i < 8; i++) {
    s_slots[i] = lv_obj_create(screen);
    lv_obj_set_size(s_slots[i], slot, slot);
    lv_obj_set_pos(s_slots[i], slot_x + (i % 4) * (slot + slot_gap), slot_y + (i / 4) * (slot + 4));
    lv_obj_set_style_bg_color(s_slots[i], lv_color_hex(UI_COLOR_BG), 0);
    lv_obj_set_style_radius(s_slots[i], 4, 0);
    lv_obj_set_style_border_width(s_slots[i], 1, 0);
    lv_obj_set_style_border_color(s_slots[i], lv_color_hex(UI_COLOR_MUTED), 0);
    lv_obj_set_style_pad_all(s_slots[i], 0, 0);
    lv_obj_set_scrollbar_mode(s_slots[i], LV_SCROLLBAR_MODE_OFF);
    s_slot_labels[i] = lv_label_create(s_slots[i]);
    lv_label_set_text(s_slot_labels[i], "_");
    lv_obj_set_style_text_font(s_slot_labels[i], UI_FONT(14), 0);
    lv_obj_set_style_text_color(s_slot_labels[i], lv_color_hex(UI_COLOR_TITLE), 0);
    lv_obj_center(s_slot_labels[i]);
  }

  s_hint = lv_label_create(screen);
  lv_label_set_text(s_hint, TR("Type the word"));
  lv_obj_set_style_text_font(s_hint, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_hint, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(s_hint, LV_ALIGN_TOP_MID, 0, 98);

  const int suggestion_y = 106;
  for (int i = 0; i < kMaxSuggestions; i++) {
    s_matches[i] = nullptr;
    s_suggestions[i] = lv_button_create(screen);
    lv_obj_set_size(s_suggestions[i], 200, 22);
    lv_obj_align(s_suggestions[i], LV_ALIGN_TOP_MID, 0, suggestion_y + i * 22);
    lv_obj_set_style_bg_color(s_suggestions[i], lv_color_hex(UI_COLOR_BUTTON), 0);
    lv_obj_set_style_bg_color(s_suggestions[i], lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
    lv_obj_set_style_radius(s_suggestions[i], 6, 0);
    lv_obj_set_style_border_width(s_suggestions[i], 0, 0);
    lv_obj_set_hidden(s_suggestions[i], true);
    lv_obj_add_event_cb(s_suggestions[i], on_suggestion, LV_EVENT_CLICKED, reinterpret_cast<void *>(static_cast<intptr_t>(i)));

    s_suggestion_labels[i] = lv_label_create(s_suggestions[i]);
    lv_label_set_text(s_suggestion_labels[i], "");
    lv_obj_set_style_text_font(s_suggestion_labels[i], UI_FONT(14), 0);
    lv_obj_set_style_text_color(s_suggestion_labels[i], lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_center(s_suggestion_labels[i]);
  }

  s_pad = lv_obj_create(screen);
  lv_obj_set_size(s_pad, 240, 250);
  lv_obj_set_pos(s_pad, 0, 112);
  lv_obj_set_style_bg_opa(s_pad, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(s_pad, 0, 0);
  lv_obj_set_style_pad_all(s_pad, 0, 0);
  lv_obj_set_scrollbar_mode(s_pad, LV_SCROLLBAR_MODE_OFF);

  const int key_w = 72;
  const int key_h = 26;
  const int button_h = 37;
  const int gap = 8;
  const int origin_x = (240 - (key_w * 3 + gap * 2)) / 2;
  const int origin_y = 10;
  const char *labels[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
  for (int i = 0; i < 8; i++) {
    const int col = i % 3;
    const int row = i / 3;
    add_key(s_pad, labels[i], origin_x + col * (key_w + gap), origin_y + row * (key_h + gap),
            key_w, key_h, on_group, reinterpret_cast<void *>(static_cast<intptr_t>(i)));
  }
  add_key(s_pad, TR("Del"), origin_x + 2 * (key_w + gap), origin_y + 2 * (key_h + gap), key_w, key_h, on_backspace, nullptr);
  const int action_w = key_w * 3 + gap * 2;
  const int final_y = 3 * (key_h + gap);
  const int cancel_y = origin_y + final_y + button_h + gap;
  s_final_button = lv_button_create(s_pad);
  lv_obj_set_pos(s_final_button, origin_x, origin_y + final_y);
  lv_obj_set_size(s_final_button, action_w, button_h);
  lv_obj_set_style_bg_color(s_final_button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_bg_color(s_final_button, lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
  lv_obj_set_style_radius(s_final_button, 8, 0);
  lv_obj_set_style_border_width(s_final_button, 0, 0);
  lv_obj_add_event_cb(s_final_button, on_select_24th, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *final_label = lv_label_create(s_final_button);
  lv_label_set_text(final_label, TR("Select 24th Word"));
  lv_obj_set_style_text_font(final_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(final_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(final_label);
  lv_obj_set_hidden(s_final_button, true);
  add_key(s_pad, TR("Cancel"), origin_x, cancel_y, action_w, button_h, on_back, nullptr);

  s_words_screen_active = true;
  refresh();
  ui_screen_replace(screen);
}
void ui_import_wallet_words_wipe(void) {
  secure_wipe(s_letters, sizeof(s_letters));
  s_len = 0;
  s_editing = false;
  s_suppress_select = false;
  s_last_group = -1;
  s_cycle = 0;
  s_word = 0;
  for (int i = 0; i < 24; ++i) s_chosen[i] = nullptr;
  for (int i = 0; i < kMaxSuggestions; ++i) s_matches[i] = nullptr;
  if (s_cycle_timer) lv_timer_pause(s_cycle_timer);
}