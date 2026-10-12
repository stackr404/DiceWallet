#include <ctype.h>
#include <string.h>
#include <lvgl.h>
#include <esp_heap_caps.h>
#include <esp_memory_utils.h>
#include "app/secure_mem.h"
#include "app/passphrase_limits.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_wallet_passphrase.h"
#include "ui/screens/ui_wallet_view_public_keys.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static char s_passphrase[kPassphraseMax + 1];
static char s_last_good[kPassphraseMax + 1];
static lv_obj_t *s_input = nullptr;
static lv_obj_t *s_status = nullptr;

void ui_wallet_passphrase_clear(void) {
  secure_wipe(s_passphrase, sizeof(s_passphrase));
  secure_wipe(s_last_good, sizeof(s_last_good));
  if (s_input != nullptr) {
    char *text = const_cast<char *>(lv_textarea_get_text(s_input));
    if (text != nullptr && (esp_ptr_internal(text) || esp_ptr_external_ram(text))) {
      secure_wipe(text, strlen(text));
    }
    lv_textarea_set_text(s_input, "");
  }
}

const char *ui_wallet_passphrase(void) {
  return s_passphrase;
}

static const char kAcceptedAscii[] =
    " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

static bool allowed(char c) {
  const unsigned char u = static_cast<unsigned char>(c);
  return u >= 0x20 && u <= 0x7E;
}

static bool passphrase_ok(const char *text) {
  if (text == nullptr) return false;
  const size_t n = strlen(text);
  if (n > static_cast<size_t>(kPassphraseMax)) return false;
  for (size_t i = 0; i < n; ++i) {
    if (!allowed(text[i])) return false;
  }
  return true;
}

static void set_status(const char *message) {
  if (s_status != nullptr) lv_label_set_text(s_status, message);
}

static void sanitize(void) {
  if (s_input == nullptr) return;
  const char *text = lv_textarea_get_text(s_input);
  if (passphrase_ok(text)) {
    strncpy(s_last_good, text, kPassphraseMax);
    s_last_good[kPassphraseMax] = '\0';
    set_status("");
    return;
  }
  lv_textarea_set_text(s_input, s_last_good);
  set_status(TR("ASCII only, 128 max. Unicode is not supported."));
}

static void finish(const char *value) {
  if (!passphrase_ok(value)) {
    set_status(TR("ASCII only, 128 max. Unicode is not supported."));
    return;
  }
  strncpy(s_passphrase, value, kPassphraseMax);
  s_passphrase[kPassphraseMax] = '\0';
  s_input = nullptr;
  s_status = nullptr;
  ui_wallet_view_public_keys_show();
}

static void on_changed(lv_event_t *event) {
  (void)event;
  sanitize();
}

static void on_ready(lv_event_t *event) {
  (void)event;
  sanitize();
  finish(s_input != nullptr ? lv_textarea_get_text(s_input) : "");
}

static void on_skip(lv_event_t *event) {
  (void)event;
  finish("");
}

void ui_wallet_passphrase_show(void) {
  s_passphrase[0] = '\0';
  s_last_good[0] = '\0';
  s_input = nullptr;
  s_status = nullptr;

  lv_obj_t *screen = ui_make_screen();

  lv_obj_t *title = ui_make_title(screen, TR("Passphrase"));

  lv_obj_t *hint = lv_label_create(screen);
  lv_label_set_text(hint, TR("Printable ASCII only, 128 max. Empty means none."));
  lv_obj_set_width(hint, 220);
  lv_label_set_long_mode(hint, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(hint, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(hint, UI_FONT(14), 0);
  lv_obj_set_style_text_color(hint, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(hint, LV_ALIGN_TOP_MID, 0, 48);

  const int input_w = 158;
  const int skip_w = 52;
  const int gap = 6;
  const int row_x = (240 - (input_w + gap + skip_w)) / 2;
  const int row_y = 96;

  s_input = lv_textarea_create(screen);
  lv_obj_set_size(s_input, input_w, 36);
  lv_obj_set_pos(s_input, row_x, row_y);
  lv_textarea_set_one_line(s_input, true);
  lv_textarea_set_max_length(s_input, kPassphraseMax);
  lv_textarea_set_accepted_chars(s_input, kAcceptedAscii);
  lv_textarea_set_placeholder_text(s_input, TR("Empty for none"));
  lv_obj_add_event_cb(s_input, on_changed, LV_EVENT_VALUE_CHANGED, nullptr);

  lv_obj_t *skip = lv_button_create(screen);
  lv_obj_set_size(skip, skip_w, 36);
  lv_obj_set_pos(skip, row_x + input_w + gap, row_y);
  lv_obj_set_style_bg_color(skip, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(skip, 6, 0);
  lv_obj_set_style_border_width(skip, 0, 0);
  lv_obj_set_style_pad_hor(skip, 6, 0);
  lv_obj_add_event_cb(skip, on_skip, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *skip_label = lv_label_create(skip);
  lv_label_set_text(skip_label, TR("Skip"));
  lv_obj_set_style_text_font(skip_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(skip_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(skip_label);

  s_status = lv_label_create(screen);
  lv_label_set_text(s_status, "");
  lv_obj_set_width(s_status, 220);
  lv_label_set_long_mode(s_status, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(s_status, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(s_status, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_status, lv_color_hex(UI_COLOR_TITLE), 0);
  lv_obj_align(s_status, LV_ALIGN_TOP_MID, 0, 140);

  lv_obj_t *kb = lv_keyboard_create(screen);
  lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_TEXT_LOWER);
  lv_keyboard_set_textarea(kb, s_input);
  lv_obj_add_event_cb(kb, on_ready, LV_EVENT_READY, nullptr);

  ui_screen_replace(screen);
}