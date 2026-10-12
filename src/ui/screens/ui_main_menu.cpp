#include <Arduino.h>
#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_new_wallet.h"
#include "ui/screens/ui_import_wallet_method.h"
#include "ui/screens/ui_settings_menu.h"
#include "ui/screens/ui_exit_system.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "app/wallet.h"
#include "ui/text/ui_text.h"

static void on_new_wallet_clicked(lv_event_t *event) {
  (void)event;
  ui_new_wallet_show();
}

static void on_import_wallet_clicked(lv_event_t *event) {
  (void)event;
  ui_import_wallet_method_show();
}

static void on_settings_clicked(lv_event_t *event) {
  (void)event;
  ui_settings_menu_show();
}

static void on_exit_clicked(lv_event_t *event) {
  (void)event;
  ui_exit_system_show();
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

void ui_main_menu_show(void) {
  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Dice Wallet"));

  make_menu_button(screen, TR("New Wallet"), 83, on_new_wallet_clicked);
  make_menu_button(screen, TR("Import Wallet"), 135, on_import_wallet_clicked);
  make_menu_button(screen, TR("Settings"), 187, on_settings_clicked);
  make_menu_button(screen, TR("Exit"), 239, on_exit_clicked);

  lv_screen_load(screen);
}