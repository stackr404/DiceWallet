#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_settings_menu.h"
#include "ui/screens/ui_settings_about.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/screens/ui_settings_screen.h"
#include "ui/screens/ui_settings_advanced.h"
#include "ui/screens/ui_settings_language.h"
//#include "ui/screens/ui_settings_predelivery.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static void on_about(lv_event_t *event) {
  (void)event;
  ui_settings_about_show();
}

static void on_screen(lv_event_t *event) {
  (void)event;
  ui_settings_screen_show();
}

static void on_advanced(lv_event_t *event) {
  (void)event;
  ui_settings_advanced_show();
}

static void on_language(lv_event_t *event) {
  (void)event;
  ui_settings_language_show();
}

// static void on_pre_delivery(lv_event_t *event) {
//   (void)event;
//   ui_settings_predelivery_show();
// }

static void on_menu(lv_event_t *event) {
  (void)event;
  ui_main_menu_show();
}

static lv_obj_t *make_menu_button(lv_obj_t *parent, const char *text, int y, lv_event_cb_t on_click) {
  lv_obj_t *button = lv_button_create(parent);
  lv_obj_set_size(button, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_set_pos(button, 20, y);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
  lv_obj_set_style_radius(button, 8, 0);
  lv_obj_set_style_border_width(button, 0, 0);
  lv_obj_add_event_cb(button, on_click, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);
  return button;
}

void ui_settings_menu_show(void) {
  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Settings"));

  lv_obj_t *rule = lv_obj_create(screen);
  lv_obj_set_size(rule, 180, 2);
  lv_obj_align(rule, LV_ALIGN_TOP_MID, 0, 40);
  lv_obj_set_style_bg_color(rule, lv_color_hex(UI_COLOR_TITLE), 0);
  lv_obj_set_style_border_width(rule, 0, 0);
  lv_obj_set_style_radius(rule, 0, 0);
  lv_obj_set_scrollable(rule, false);

  const int y = 68;
  const int y_padding = 10;
  make_menu_button(screen, TR("About"), y, on_about);
  make_menu_button(screen, TR("Screen"), y + y_padding + UI_BUTTON_HEIGHT, on_screen);
  make_menu_button(screen, TR("Advanced"), y + y_padding * 2 + UI_BUTTON_HEIGHT * 2, on_advanced);
  make_menu_button(screen, TR("Language"), y + y_padding * 3 + UI_BUTTON_HEIGHT * 3, on_language);
  // if (!ui_settings_predelivery_done()) {
  //   make_menu_button(screen, TR("Pre-delivery"), 224, on_pre_delivery);
  //   make_menu_button(screen, TR("Main Menu"), 268, on_menu);
  // } else {
    make_menu_button(screen, TR("Main Menu"), y + y_padding * 4 + UI_BUTTON_HEIGHT * 4, on_menu);
  //}

  ui_screen_replace(screen);
}