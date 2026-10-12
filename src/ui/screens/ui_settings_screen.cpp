#include <stdio.h>
#include <Arduino.h>
#include <Preferences.h>
#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_settings_screen.h"
#include "ui/screens/ui_settings_menu.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static const int kBacklightPin = 21;
static const char *kNamespace = "dicewallet";
static const char *kKeyBrightness = "bright";
static const char *kKeyOffSeconds = "offsec";

static Preferences s_prefs;
static int s_brightness = 200;
static int s_off_seconds = 30;
static bool s_ready = false;
static bool s_blanked = false;
static bool s_swallow = false;
static bool s_hold_awake = false;
static lv_obj_t *s_timeout_label = nullptr;

static void apply_brightness(int value);
static void save_settings(void);
static void update_timeout_label(void);

bool ui_settings_screen_is_blanked(void) { return s_blanked; }
bool ui_settings_screen_swallowing(void) { return s_swallow; }
void ui_settings_screen_swallow_done(void) { s_swallow = false; }

void ui_settings_screen_wake(void) {
  s_blanked = false;
  s_swallow = true;
  apply_brightness(s_brightness);
  lv_display_t *display = lv_display_get_default();
  if (display != nullptr) lv_display_trigger_activity(display);
}

void ui_settings_screen_hold_awake(bool hold) {
  s_hold_awake = hold;
  if (hold) ui_settings_screen_wake();
}

static void apply_brightness(int value) {
  if (!s_ready) {
    ledcAttach(kBacklightPin, 5000, 8);
    s_ready = true;
  }
  ledcWrite(kBacklightPin, value);
}

static void save_settings(void) {
  s_prefs.begin(kNamespace, false);
  s_prefs.putUChar(kKeyBrightness, static_cast<uint8_t>(s_brightness));
  s_prefs.putUChar(kKeyOffSeconds, static_cast<uint8_t>(s_off_seconds));
  s_prefs.end();
}

static void update_timeout_label(void) {
  if (s_timeout_label == nullptr) return;
  char text[40];
  if (s_off_seconds >= 120) snprintf(text, sizeof(text), TR("Screen off: never"));
  else snprintf(text, sizeof(text), TR("Screen off after %d sec"), s_off_seconds);
  lv_label_set_text(s_timeout_label, text);
}

static void on_brightness(lv_event_t *event) {
  s_brightness = lv_slider_get_value(static_cast<lv_obj_t *>(lv_event_get_target(event)));
  apply_brightness(s_brightness);
  save_settings();
}

static void on_timeout(lv_event_t *event) {
  s_off_seconds = lv_slider_get_value(static_cast<lv_obj_t *>(lv_event_get_target(event)));
  update_timeout_label();
  save_settings();
}

static void on_back(lv_event_t *event) {
  (void)event;
  s_timeout_label = nullptr;
  ui_settings_menu_show();
}

static void style_slider(lv_obj_t *slider) {
  lv_obj_set_style_bg_color(slider, lv_color_hex(UI_COLOR_BUTTON), LV_PART_MAIN);
  lv_obj_set_style_bg_color(slider, lv_color_hex(UI_COLOR_TITLE), LV_PART_INDICATOR);
  lv_obj_set_style_bg_color(slider, lv_color_hex(UI_COLOR_TITLE), LV_PART_KNOB);
}

void ui_settings_screen_init(void) {
  s_prefs.begin(kNamespace, true);
  s_brightness = s_prefs.getUChar(kKeyBrightness, 200);
  s_off_seconds = s_prefs.getUChar(kKeyOffSeconds, 30);
  s_prefs.end();
  if (s_brightness < 15) s_brightness = 15;
  if (s_brightness > 255) s_brightness = 255;
  if (s_off_seconds < 5) s_off_seconds = 5;
  if (s_off_seconds > 120) s_off_seconds = 120;
  apply_brightness(s_brightness);
}

void ui_settings_screen_show(void) {
  s_timeout_label = nullptr;

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Screen"));


  lv_obj_t *bright_label = lv_label_create(screen);
  lv_label_set_text(bright_label, TR("Brightness"));
  lv_obj_set_style_text_font(bright_label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(bright_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(bright_label, LV_ALIGN_TOP_MID, 0, 74);

  lv_obj_t *bright = lv_slider_create(screen);
  lv_obj_set_size(bright, 200, 16);
  lv_obj_align(bright, LV_ALIGN_TOP_MID, 0, 102);
  lv_slider_set_range(bright, 15, 255);
  lv_slider_set_value(bright, s_brightness, LV_ANIM_OFF);
  style_slider(bright);
  lv_obj_add_event_cb(bright, on_brightness, LV_EVENT_VALUE_CHANGED, nullptr);

  s_timeout_label = lv_label_create(screen);
  lv_obj_set_style_text_font(s_timeout_label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(s_timeout_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(s_timeout_label, LV_ALIGN_TOP_MID, 0, 150);
  update_timeout_label();

  lv_obj_t *timeout = lv_slider_create(screen);
  lv_obj_set_size(timeout, 200, 16);
  lv_obj_align(timeout, LV_ALIGN_TOP_MID, 0, 178);
  lv_slider_set_range(timeout, 5, 120);
  lv_slider_set_value(timeout, s_off_seconds, LV_ANIM_OFF);
  style_slider(timeout);
  lv_obj_add_event_cb(timeout, on_timeout, LV_EVENT_VALUE_CHANGED, nullptr);

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

void ui_settings_screen_poll(void) {
  lv_display_t *display = lv_display_get_default();
  if (display == nullptr) return;
  if (s_hold_awake) {
    s_blanked = false;
    apply_brightness(s_brightness);
    lv_display_trigger_activity(display);
    return;
  }
  if (s_off_seconds >= 120) {
    s_blanked = false;
    apply_brightness(s_brightness);
    return;
  }
  const uint32_t idle = lv_display_get_inactive_time(display);
  if (idle >= static_cast<uint32_t>(s_off_seconds) * 1000) {
    s_blanked = true;
    apply_brightness(0);
  } else if (!s_blanked) {
    apply_brightness(s_brightness);
  }
}
