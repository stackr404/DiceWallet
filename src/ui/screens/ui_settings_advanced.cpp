#include <stdio.h>
#include <string.h>
#include <Arduino.h>
#include <Preferences.h>
#include <esp_system.h>
#include <lvgl.h>
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "dice/die_rolls.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_settings_menu.h"
#include "ui/screens/ui_settings_advanced.h"
#include "ui/screens/ui_wallet_passphrase.h"
#include "ui/screens/ui_exit_system.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static const char *kNamespace = "dicewallet";
static const char *kKeyAdvanced = "advanced";
static const char *kKeyWipeMinutes = "wipemin";
static const char *kKeyRollCount = "rollcount";
// static const int kRollCountDefault = 128;
// static const int kRollCountMin = 100;
// static const int kRollCountMax = 200;

static Preferences s_prefs;
static bool s_advanced = false;
static int s_wipe_minutes = 10;
static int s_die_roll_count = k_default_die_rolls;
static bool s_wiping = false;
static lv_obj_t *s_mode_label = nullptr;
static lv_obj_t *s_wipe_label = nullptr;
static lv_obj_t *s_roll_label = nullptr;

bool ui_settings_advanced_enabled(void) {
  return s_advanced;
}

static int clamp_roll_count(int count) {
  if (count < k_min_die_rolls) return k_min_die_rolls;
  if (count > k_max_die_rolls) return k_max_die_rolls;
  return count;
}

int ui_settings_die_roll_count(void) {
  return s_die_roll_count;
}

static void save_mode(void) {
  s_prefs.begin(kNamespace, false);
  s_prefs.putBool(kKeyAdvanced, s_advanced);
  s_prefs.end();
}

static void save_wipe(void) {
  s_prefs.begin(kNamespace, false);
  s_prefs.putUChar(kKeyWipeMinutes, static_cast<uint8_t>(s_wipe_minutes));
  s_prefs.end();
}

static void save_roll_count(void) {
  s_prefs.begin(kNamespace, false);
  s_prefs.putUChar(kKeyRollCount, static_cast<uint8_t>(s_die_roll_count));
  s_prefs.end();
}

static void update_mode_label(void) {
  if (s_mode_label == nullptr) return;
  lv_label_set_text(s_mode_label, s_advanced ? TR("Wallet mode: Advanced") : TR("Wallet mode: Simple"));
}

static void update_wipe_label(void) {
  if (s_wipe_label == nullptr) return;
  char text[40];
  if (s_wipe_minutes >= 60) snprintf(text, sizeof(text), TR("Wipe device: never"));
  else if (s_wipe_minutes == 1) snprintf(text, sizeof(text), TR("Wipe device after 1 minute"));
  else snprintf(text, sizeof(text), TR("Wipe device after %d minutes"), s_wipe_minutes);
  lv_label_set_text(s_wipe_label, text);
}

static void on_toggle(lv_event_t *event) {
  s_advanced = lv_obj_has_state(static_cast<lv_obj_t *>(lv_event_get_target(event)), LV_STATE_CHECKED);
  update_mode_label();
  save_mode();
}

static void on_wipe(lv_event_t *event) {
  s_wipe_minutes = lv_slider_get_value(static_cast<lv_obj_t *>(lv_event_get_target(event)));
  update_wipe_label();
  save_wipe();
}

static void update_roll_label(void) {
  if (s_roll_label == nullptr) return;
  char text[40];
  snprintf(text, sizeof(text), TR("Die rolls: %d"), s_die_roll_count);
  lv_label_set_text(s_roll_label, text);
}

static void on_roll_count(lv_event_t *event) {
  s_die_roll_count = clamp_roll_count(lv_slider_get_value(static_cast<lv_obj_t *>(lv_event_get_target(event))));
  update_roll_label();
  save_roll_count();
}

static void on_back(lv_event_t *event) {
  (void)event;
  s_mode_label = nullptr;
  s_wipe_label = nullptr;
  s_roll_label = nullptr;
  ui_settings_menu_show();
}

void ui_settings_advanced_init(void) {
  s_prefs.begin(kNamespace, true);
  s_advanced = s_prefs.getBool(kKeyAdvanced, false);
  s_wipe_minutes = s_prefs.getUChar(kKeyWipeMinutes, 10);
  s_die_roll_count = clamp_roll_count(s_prefs.getUChar(kKeyRollCount, k_default_die_rolls));
  s_prefs.end();
  if (s_wipe_minutes < 1) s_wipe_minutes = 1;
  if (s_wipe_minutes > 60) s_wipe_minutes = 60;
}

void ui_settings_advanced_show(void) {
  ui_settings_advanced_init();

  s_mode_label = nullptr;
  s_wipe_label = nullptr;
  s_roll_label = nullptr;

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Advanced"));


  s_mode_label = lv_label_create(screen);
  lv_obj_set_style_text_font(s_mode_label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_mode_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(s_mode_label, LV_ALIGN_TOP_MID, 0, 50);
  update_mode_label();

  lv_obj_t *toggle = lv_switch_create(screen);
  lv_obj_align(toggle, LV_ALIGN_TOP_MID, 0, 72);
  if (s_advanced) lv_obj_add_state(toggle, LV_STATE_CHECKED);
  lv_obj_add_event_cb(toggle, on_toggle, LV_EVENT_VALUE_CHANGED, nullptr);

  s_roll_label = lv_label_create(screen);
  lv_obj_set_style_text_font(s_roll_label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_roll_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(s_roll_label, LV_ALIGN_TOP_MID, 0, 118);
  update_roll_label();

  lv_obj_t *rolls = lv_slider_create(screen);
  lv_obj_set_size(rolls, 200, 16);
  lv_obj_align(rolls, LV_ALIGN_TOP_MID, 0, 142);
  lv_slider_set_range(rolls, k_min_die_rolls, k_max_die_rolls);
  lv_slider_set_value(rolls, s_die_roll_count, LV_ANIM_OFF);
  lv_obj_set_style_bg_color(rolls, lv_color_hex(UI_COLOR_BUTTON), LV_PART_MAIN);
  lv_obj_set_style_bg_color(rolls, lv_color_hex(UI_COLOR_TITLE), LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(rolls, lv_color_hex(UI_COLOR_TITLE), LV_PART_KNOB);
  lv_obj_add_event_cb(rolls, on_roll_count, LV_EVENT_VALUE_CHANGED, nullptr);

  s_wipe_label = lv_label_create(screen);
  lv_obj_set_style_text_font(s_wipe_label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_wipe_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(s_wipe_label, LV_ALIGN_TOP_MID, 0, 178);
  update_wipe_label();

  lv_obj_t *wipe = lv_slider_create(screen);
  lv_obj_set_size(wipe, 200, 16);
  lv_obj_align(wipe, LV_ALIGN_TOP_MID, 0, 202);
  lv_slider_set_range(wipe, 1, 60);
  lv_slider_set_value(wipe, s_wipe_minutes, LV_ANIM_OFF);
  lv_obj_set_style_bg_color(wipe, lv_color_hex(UI_COLOR_BUTTON), LV_PART_MAIN);
  lv_obj_set_style_bg_color(wipe, lv_color_hex(UI_COLOR_TITLE), LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(wipe, lv_color_hex(UI_COLOR_TITLE), LV_PART_KNOB);
  lv_obj_add_event_cb(wipe, on_wipe, LV_EVENT_VALUE_CHANGED, nullptr);

  lv_obj_t *button = lv_button_create(screen);
  lv_obj_set_size(button, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(button, 8, 0);
  lv_obj_set_style_border_width(button, 0, 0);
  lv_obj_add_event_cb(button, on_back, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, TR("Back"));
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);

  ui_screen_replace(screen);
}

void ui_settings_advanced_poll(void) {
  if (s_wiping || s_wipe_minutes >= 60) return;
  lv_display_t *display = lv_display_get_default();
  if (display == nullptr) return;
  const uint32_t idle = lv_display_get_inactive_time(display);
  if (idle < static_cast<uint32_t>(s_wipe_minutes) * 60000) return;
  s_wiping = true;
  device_wipe_secrets();
  device_scrub_residue();
  ui_exit_system_show();
}
