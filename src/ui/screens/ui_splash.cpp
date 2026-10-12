#include <esp_ota_ops.h>
#include <esp_partition.h>
#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_splash.h"
#include "ui/screens/ui_main_menu.h"
#include <esp_secure_boot.h>
#include "ui/theme/ui_theme.h"
#include "ui/text/ui_text.h"
#include "ui/ui_nav.h"
#include "app/firmware_hash.h"

static uint8_t s_hash[32];
static bool s_secured = false;

static const uint32_t kColors[6] = {
    0xE03131, // red
    0xFAB005, // yellow
    0x4C6EF5, // blue
    0xFD7E14, // orange
    0x12B886, // green
    0xAE3EC9  // purple
};

static bool firmware_locked(void)
{
  return esp_secure_boot_enabled();
}

static void load_hash(void)
{
  firmware_partition_sha256(s_hash);
}

static void on_identicon_draw(lv_event_t *event)
{
  if (lv_event_get_code(event) != LV_EVENT_DRAW_MAIN)
    return;
  lv_obj_t *obj = static_cast<lv_obj_t *>(lv_event_get_target(event));
  lv_layer_t *layer = lv_event_get_layer(event);
  lv_area_t coords;
  lv_obj_get_coords(obj, &coords);

  lv_draw_rect_dsc_t dsc;
  lv_draw_rect_dsc_init(&dsc);
  dsc.bg_opa = LV_OPA_COVER;
  dsc.border_width = 0;
  dsc.radius = 0;
  dsc.bg_color = lv_color_hex(kColors[s_hash[3] % 6]);

  const int cell = 16;
  const int gap = 2;
  for (int row = 0; row < 5; row++)
  {
    for (int col = 0; col < 5; col++)
    {
      const int source = col < 3 ? col : 4 - col;
      if ((s_hash[row] & (1u << source)) == 0)
        continue;
      const int x = coords.x1 + col * (cell + gap);
      const int y = coords.y1 + row * (cell + gap);
      lv_area_t tile = {x, y, x + cell - 1, y + cell - 1};
      lv_draw_rect(layer, &dsc, &tile);
    }
  }
}

static void on_continue(lv_event_t *event)
{
  (void)event;
  ui_main_menu_show();
}

void ui_splash_show(void)
{

  s_secured = firmware_locked();
  load_hash();

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, s_secured ? TR("Secure Boot On") : TR("Secure Boot Off"));

  lv_obj_t *status = lv_label_create(screen);
  lv_label_set_text(status, s_secured
                                ? TR("Secure boot is enabled. Only signed firmware will run.")
                                : TR("Secure boot is off. Unsigned firmware can run."));
  lv_obj_set_width(status, 210);
  lv_label_set_long_mode(status, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(status, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(status, UI_FONT(14), 0);
  lv_obj_set_style_text_color(status, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(status, LV_ALIGN_TOP_MID, 0, 57);

  lv_obj_t *icon = lv_obj_create(screen);
  lv_obj_set_size(icon, 5 * 18, 5 * 18);
  lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 115);
  lv_obj_set_style_bg_opa(icon, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(icon, 0, 0);
  lv_obj_set_scrollable(icon, false);
  lv_obj_set_clickable(icon, false);
  lv_obj_add_event_cb(icon, on_identicon_draw, LV_EVENT_DRAW_MAIN, nullptr);

  lv_obj_t *warning = lv_label_create(screen);
  lv_label_set_text(warning, TR("If this image changes, the firmware has changed."));
  lv_obj_set_width(warning, 210);
  lv_label_set_long_mode(warning, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(warning, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(warning, UI_FONT(14), 0);
  lv_obj_set_style_text_color(warning, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(warning, LV_ALIGN_TOP_MID, 0, 217);

  lv_obj_t *button = lv_button_create(screen);
  lv_obj_set_size(button, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(button, 8, 0);
  lv_obj_set_style_border_width(button, 0, 0);
  lv_obj_add_event_cb(button, on_continue, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, TR("Continue"));
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);

  ui_screen_replace(screen);
}