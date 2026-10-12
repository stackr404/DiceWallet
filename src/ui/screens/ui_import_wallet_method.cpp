#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_import_wallet_method.h"
#include "ui/screens/ui_settings_advanced.h"
#include "ui/screens/ui_import_wallet_words.h"
#include "ui/screens/ui_import_wallet_words_index.h"
#include "ui/screens/ui_import_wallet_words_hex.h"
#include "ui/screens/ui_import_wallet_words_bin.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static void on_main_menu(lv_event_t *event) {
  (void)event;
  ui_main_menu_show();
}

static void on_word(lv_event_t *event) {
  (void)event;
  ui_import_wallet_words_show();
}

static void on_word_index(lv_event_t *event) {
  (void)event;
  ui_import_wallet_words_index_show();
}

static void on_word_hex(lv_event_t *event) {
  (void)event;
  ui_import_wallet_words_hex_show();
}

static void on_word_bin(lv_event_t *event) {
  (void)event;
  ui_import_wallet_words_bin_show();
}

static lv_obj_t *add_method_button(lv_obj_t *screen, const char *text, int y, lv_event_cb_t handler) {
  lv_obj_t *button = lv_button_create(screen);
  lv_obj_set_size(button, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(button, LV_ALIGN_TOP_MID, 0, y);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
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

void ui_import_wallet_method_show(void) {
  lv_obj_t *screen = ui_make_screen();

  lv_obj_t *title = ui_make_title(screen, TR("Import Method"));

  add_method_button(screen, TR("24 Words"), 64, on_word);
  if (ui_settings_advanced_enabled()) {
    add_method_button(screen, TR("24 INT Indexes"), 112, on_word_index);
    add_method_button(screen, TR("24 HEX Indexes"), 160, on_word_hex);
    add_method_button(screen, TR("24 BIN Indexes"), 208, on_word_bin);
  }

  lv_obj_t *back = lv_button_create(screen);
  lv_obj_set_size(back, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(back, UI_BUTTON_BOTTOM_ALIGN, 0, -12);
  lv_obj_set_style_bg_color(back, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_bg_color(back, lv_color_hex(UI_COLOR_PRESSED), LV_STATE_PRESSED);
  lv_obj_set_style_radius(back, 8, 0);
  lv_obj_set_style_border_width(back, 0, 0);
  lv_obj_add_event_cb(back, on_main_menu, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *back_label = lv_label_create(back);
  lv_label_set_text(back_label, TR("Main Menu"));
  lv_obj_set_style_text_font(back_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(back_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(back_label);

  ui_screen_replace(screen);
}