#include <cstdio>
#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_settings_about.h"
#include "ui/screens/ui_settings_menu.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "app/version.h"
#include "app/firmware_hash.h"
#include "ui/text/ui_text.h"

static void on_menu(lv_event_t *event) {
  (void)event;
  ui_settings_menu_show();
}

static lv_obj_t *add_paragraph(lv_obj_t *screen, const char *text, int y) {
  lv_obj_t *label = lv_label_create(screen);
  lv_label_set_text(label, text);
  lv_obj_set_width(label, 220);
  lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(label, UI_FONT(14), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_MUTED), 0);
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, y);
  return label;
}

void ui_settings_about_show(void) {
  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("About"));

  lv_obj_t *version = lv_label_create(screen);
  lv_label_set_text(version, DICEWALLET_VERSION);
  lv_obj_set_style_text_font(version, UI_FONT(14), 0);
  lv_obj_set_style_text_color(version, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(version, LV_ALIGN_TOP_MID, 0, 47);

  add_paragraph(screen, TR("Amnesic offline dice wallet."), 65);
  add_paragraph(screen, TR("No seed is stored after use."), 84);
  add_paragraph(screen, TR("Works fully offline."), 106);
  add_paragraph(screen, TR("Entropy is from your dice rolls, not a random number generator."), 128);

  char hash_hex[65];
  firmware_hash_hex(hash_hex);
  char hash_lines[96];
  // 16 hex chars fit in Montserrat 12. A 32-char line wraps its last glyph.
  snprintf(hash_lines, sizeof(hash_lines), "%s\n%.16s\n%.16s\n%.16s\n%.16s",
           TR("Firmware SHA-256"),
           hash_hex, hash_hex + 16, hash_hex + 32, hash_hex + 48);
  lv_obj_t *hash = lv_label_create(screen);
  lv_label_set_text(hash, hash_lines);
  lv_obj_set_width(hash, 220);
  lv_label_set_long_mode(hash, LV_LABEL_LONG_CLIP);
  lv_obj_set_style_text_align(hash, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(hash, &lv_font_montserrat_12, 0);
  lv_obj_set_style_text_color(hash, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_align(hash, LV_ALIGN_TOP_MID, 0, 180);

  lv_obj_t *button = lv_button_create(screen);
  lv_obj_set_size(button, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(button, 8, 0);
  lv_obj_set_style_border_width(button, 0, 0);
  lv_obj_add_event_cb(button, on_menu, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, TR("Back"));
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);

  ui_screen_replace(screen);
}