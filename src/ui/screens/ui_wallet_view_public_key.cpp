#include <lvgl.h>
#include <string.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/screens/ui_wallet_view_public_key.h"
#include "ui/screens/ui_wallet_view_public_keys.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "ui/text/ui_text.h"

static void on_back(lv_event_t *event) {
  (void)event;
  ui_wallet_view_public_keys_show();
}

static void on_finish(lv_event_t *event) {
  (void)event;
  device_wipe_secrets();
  ui_main_menu_show();
  device_scrub_residue();
}

void ui_wallet_view_public_key_show(const char *coin, const char *key, const char *path) {
  lv_obj_t *screen = ui_make_screen();

  lv_obj_t *title = ui_make_title(screen, coin != nullptr ? coin : "");
  
  lv_obj_t *qr = lv_qrcode_create(screen);
  lv_qrcode_set_size(qr, 108);
  lv_qrcode_set_dark_color(qr, lv_color_hex(0x000000));
  lv_qrcode_set_light_color(qr, lv_color_hex(0xFFFFFF));
  const char *payload = key != nullptr ? key : "";
  lv_qrcode_update(qr, payload, strlen(payload));
  lv_obj_align(qr, LV_ALIGN_TOP_MID, 0, 49);

  lv_obj_t *key_label = lv_label_create(screen);
  lv_label_set_text(key_label, payload);
  lv_obj_set_width(key_label, 220);
  lv_label_set_long_mode(key_label, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(key_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(key_label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(key_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(key_label, LV_ALIGN_TOP_MID, 0, 163);

  lv_obj_t *path_label = lv_label_create(screen);
  lv_label_set_text(path_label, path != nullptr ? path : "");
  lv_obj_set_width(path_label, 220);
  lv_label_set_long_mode(path_label, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(path_label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(path_label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(path_label, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(path_label, LV_ALIGN_TOP_MID, 0, 251);

  lv_obj_t *back = lv_button_create(screen);
  lv_obj_set_size(back, UI_BUTTON_HALF_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(back, LV_ALIGN_BOTTOM_LEFT, 16, -6);
  lv_obj_set_style_bg_color(back, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(back, 8, 0);
  lv_obj_set_style_border_width(back, 0, 0);
  lv_obj_add_event_cb(back, on_back, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *back_label = lv_label_create(back);
  lv_label_set_text(back_label, TR("Back"));
  lv_obj_set_style_text_font(back_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(back_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(back_label);

  lv_obj_t *finish = lv_button_create(screen);
  lv_obj_set_size(finish, UI_BUTTON_HALF_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(finish, LV_ALIGN_BOTTOM_RIGHT, -16, -6);
  lv_obj_set_style_bg_color(finish, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(finish, 8, 0);
  lv_obj_set_style_border_width(finish, 0, 0);
  lv_obj_add_event_cb(finish, on_finish, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *finish_label = lv_label_create(finish);
  lv_label_set_text(finish_label, TR("Finish"));
  lv_obj_set_style_text_font(finish_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(finish_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(finish_label);

  ui_screen_replace(screen);
}