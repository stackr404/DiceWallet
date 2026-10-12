#include <Arduino.h>
#include <Preferences.h>
#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_settings_language.h"
#include "ui/screens/ui_settings_menu.h"
#include "ui/text/ui_text.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"

static const char *kNamespace = "dicewallet";
static const char *kKeyLanguage = "lang";

struct LanguageChoice {
  ui_language id;
  const char *name;
};

static const LanguageChoice kLanguages[] = {
  {UI_LANG_EN, "English"},
  {UI_LANG_FR, "French"},
  {UI_LANG_DE, "German"},
  {UI_LANG_PL, "Polish"},
  {UI_LANG_SV, "Swedish"},
  {UI_LANG_NL, "Dutch"},
  {UI_LANG_RU, "Russian"},
  {UI_LANG_IT, "Italian"},
  {UI_LANG_ZH, "Chinese"},
  {UI_LANG_JA, "Japanese"},
  {UI_LANG_KO, "Korean"},
  {UI_LANG_ES, "Spanish"},
  {UI_LANG_PT, "Portuguese"},
};

static Preferences s_prefs;
static ui_language s_language = UI_LANG_EN;
static int s_index = 0;
static lv_obj_t *s_name = nullptr;

static void save_language(ui_language language) {
  s_language = language;
  ui_text_set_language(language);
  s_prefs.begin(kNamespace, false);
  s_prefs.putUChar(kKeyLanguage, static_cast<uint8_t>(language));
  s_prefs.end();
}

static void show_name(void) {
  if (s_name == nullptr) return;
  lv_label_set_text(s_name, TR(kLanguages[s_index].name));
}

static void on_prev(lv_event_t *event) {
  (void)event;
  const int count = (int)(sizeof(kLanguages) / sizeof(kLanguages[0]));
  s_index = (s_index == 0) ? count - 1 : s_index - 1;
  show_name();
}

static void on_next(lv_event_t *event) {
  (void)event;
  const int count = (int)(sizeof(kLanguages) / sizeof(kLanguages[0]));
  s_index++;
  if (s_index >= count) s_index = 0;
  show_name();
}

static void on_select(lv_event_t *event) {
  (void)event;
  save_language(kLanguages[s_index].id);
  ui_settings_language_show();
}

static void on_back(lv_event_t *event) {
  (void)event;
  ui_settings_menu_show();
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

void ui_settings_language_init(void) {
  s_prefs.begin(kNamespace, true);
  const int stored = s_prefs.getUChar(kKeyLanguage, UI_LANG_EN);
  s_prefs.end();
  s_language = (stored >= UI_LANG_EN && stored <= UI_LANG_PT) ? static_cast<ui_language>(stored) : UI_LANG_EN;
  ui_text_set_language(s_language);
}

void ui_settings_language_show(void) {
  s_name = nullptr;
  s_index = 0;
  for (unsigned i = 0; i < sizeof(kLanguages) / sizeof(kLanguages[0]); i++) {
    if (kLanguages[i].id == s_language) s_index = (int)i;
  }

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Language"));

  s_name = lv_label_create(screen);
  lv_label_set_text(s_name, TR(kLanguages[s_index].name));
  lv_obj_set_style_text_font(s_name, UI_FONT(22), 0);
  lv_obj_set_style_text_color(s_name, lv_color_hex(UI_COLOR_TITLE), 0);
  lv_obj_align(s_name, LV_ALIGN_TOP_MID, 0, 80);

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