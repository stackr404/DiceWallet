#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_exit_system.h"
#include "ui/screens/ui_settings_screen.h"
#include "ui/assets/icon_secure_wipe.h"
#include "ui/assets/icon_unplug_power_1.h"
#include "ui/assets/icon_unplug_power_2.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "ui/text/ui_text.h"

static lv_obj_t *s_unplug = nullptr;
static lv_obj_t *s_flash = nullptr;
static lv_timer_t *s_flip = nullptr;
static lv_timer_t *s_flash_timer = nullptr;
static bool s_show_second = false;

static void draw_bitmap(lv_event_t *event, const uint8_t *bits, int width, int height) {
  if (lv_event_get_code(event) != LV_EVENT_DRAW_MAIN) return;

  lv_obj_t *obj = static_cast<lv_obj_t *>(lv_event_get_target(event));
  lv_layer_t *layer = lv_event_get_layer(event);
  lv_area_t coords;
  lv_obj_get_coords(obj, &coords);

  lv_draw_rect_dsc_t dsc;
  lv_draw_rect_dsc_init(&dsc);
  dsc.bg_opa = LV_OPA_COVER;
  dsc.bg_color = lv_color_hex(UI_COLOR_TITLE);
  dsc.border_width = 0;
  dsc.radius = 0;

  const int stride = (width + 7) / 8;

  for (int y = 0; y < height; ++y) {
    const uint8_t *row = bits + y * stride;
    int run = -1;
    for (int x = 0; x <= width; ++x) {
      const bool on = x < width &&
                      (row[x >> 3] & static_cast<uint8_t>(0x80 >> (x & 7))) != 0;
      if (on && run < 0) run = x;
      if (!on && run >= 0) {
        lv_area_t bar = {
          coords.x1 + run,
          coords.y1 + y,
          coords.x1 + x - 1,
          coords.y1 + y
        };
        lv_draw_rect(layer, &dsc, &bar);
        run = -1;
      }
    }
  }
}

static void draw_secure_wipe_icon(lv_event_t *event) {
  draw_bitmap(event, icon_secure_wipe, ICON_SECURE_WIPE_WIDTH, ICON_SECURE_WIPE_HEIGHT);
}

static void draw_unplug_icon(lv_event_t *event) {
  if (s_show_second) {
    draw_bitmap(event, icon_unplug_power_2, ICON_UNPLUG_POWER_2_WIDTH, ICON_UNPLUG_POWER_2_HEIGHT);
  } else {
    draw_bitmap(event, icon_unplug_power_1, ICON_UNPLUG_POWER_1_WIDTH, ICON_UNPLUG_POWER_1_HEIGHT);
  }
}

static void on_flip(lv_timer_t *timer) {
  (void)timer;
  s_show_second = !s_show_second;
  if (s_unplug != nullptr) lv_obj_invalidate(s_unplug);
}

static void hide_flash(lv_timer_t *timer) {
  if (s_flash != nullptr) lv_obj_set_hidden(s_flash, true);
  lv_timer_delete(timer);
}

static void on_flash(lv_timer_t *timer) {
  (void)timer;
  if (s_flash == nullptr) return;
  lv_obj_set_hidden(s_flash, false);
  lv_obj_move_foreground(s_flash);
  lv_timer_t *hide = lv_timer_create(hide_flash, 200, nullptr);
  lv_timer_set_repeat_count(hide, 1);
}

static void on_screen_delete(lv_event_t *event) {
  if (lv_event_get_code(event) != LV_EVENT_DELETE) return;
  if (s_flip != nullptr) {
    lv_timer_delete(s_flip);
    s_flip = nullptr;
  }
  if (s_flash_timer != nullptr) {
    lv_timer_delete(s_flash_timer);
    s_flash_timer = nullptr;
  }
  s_unplug = nullptr;
  s_flash = nullptr;
  ui_settings_screen_hold_awake(false);
}

void ui_exit_system_show(void) {
  device_wipe_secrets();
  device_scrub_residue();
  if (s_flip != nullptr) {
    lv_timer_delete(s_flip);
    s_flip = nullptr;
  }
  if (s_flash_timer != nullptr) {
    lv_timer_delete(s_flash_timer);
    s_flash_timer = nullptr;
  }
  s_show_second = false;
  ui_settings_screen_hold_awake(true);

  lv_obj_t *screen = ui_make_screen();
  lv_obj_add_event_cb(screen, on_screen_delete, LV_EVENT_DELETE, nullptr);

  ui_make_title(screen, TR("Secure Wipe"));

  lv_obj_t *icon = lv_obj_create(screen);
  lv_obj_set_size(icon, ICON_SECURE_WIPE_WIDTH, ICON_SECURE_WIPE_HEIGHT);
  lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 62);
  lv_obj_set_style_bg_opa(icon, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(icon, 0, 0);
  lv_obj_set_style_pad_all(icon, 0, 0);
  lv_obj_set_scrollable(icon, false);
  lv_obj_add_event_cb(icon, draw_secure_wipe_icon, LV_EVENT_DRAW_MAIN, nullptr);

  lv_obj_t *wiped = lv_label_create(screen);
  lv_label_set_text(wiped, TR("Dice rolls, seed indexes, and passphrase have been wiped from this device."));
  lv_obj_set_width(wiped, 220);
  lv_label_set_long_mode(wiped, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(wiped, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(wiped, UI_FONT(14), 0);
  lv_obj_set_style_text_color(wiped, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(wiped, LV_ALIGN_TOP_MID, 0, 170);

  lv_obj_t *power = lv_label_create(screen);
  lv_label_set_text(power, TR("Please power off device"));
  lv_obj_set_width(power, 220);
  lv_label_set_long_mode(power, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(power, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(power, UI_FONT(14), 0);
  lv_obj_set_style_text_color(power, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(power, LV_ALIGN_TOP_MID, 0, 224);

  s_unplug = lv_obj_create(screen);
  lv_obj_set_size(s_unplug, ICON_UNPLUG_POWER_1_WIDTH, ICON_UNPLUG_POWER_1_HEIGHT);
  lv_obj_align(s_unplug, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_opa(s_unplug, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(s_unplug, 0, 0);
  lv_obj_set_style_pad_all(s_unplug, 0, 0);
  lv_obj_set_scrollable(s_unplug, false);
  lv_obj_add_event_cb(s_unplug, draw_unplug_icon, LV_EVENT_DRAW_MAIN, nullptr);

  s_flash = lv_obj_create(screen);
  lv_obj_set_size(s_flash, LV_PCT(100), LV_PCT(100));
  lv_obj_set_style_bg_color(s_flash, lv_color_hex(0xFFFFFF), 0);
  lv_obj_set_style_bg_opa(s_flash, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(s_flash, 0, 0);
  lv_obj_set_style_radius(s_flash, 0, 0);
  lv_obj_set_hidden(s_flash, true);
  //lv_obj_add_flag(s_flash, LV_OBJ_FLAG_HIDDEN);
  lv_obj_set_scrollable(s_flash, false);
  //lv_obj_remove_flag(s_flash, LV_OBJ_FLAG_SCROLLABLE);

  s_flip = lv_timer_create(on_flip, 1000, nullptr);
  s_flash_timer = lv_timer_create(on_flash, 5000, nullptr);

  ui_screen_replace(screen);
}