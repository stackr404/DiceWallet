#include "ui/screens/ui_helper.h"
#include "ui/theme/ui_theme.h"
#include "ui/text/ui_text.h"

lv_obj_t *ui_make_title(lv_obj_t *parent, const char *text, bool show_rule) {
  lv_obj_t *title = lv_label_create(parent);
  lv_label_set_text(title, text);
  lv_obj_set_style_text_font(title, UI_FONT(UI_TITLE_FONT_SIZE), 0);
  lv_obj_set_style_text_color(title, lv_color_hex(UI_COLOR_TITLE), 0);
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, UI_TITLE_Y);

  if (show_rule) {
    lv_obj_t *rule = lv_obj_create(parent);
    lv_obj_set_size(rule, UI_TITLE_RULE_WIDTH, 2);
    lv_obj_align(rule, LV_ALIGN_TOP_MID, 0, UI_TITLE_RULE_Y);
    lv_obj_set_style_bg_color(rule, lv_color_hex(UI_COLOR_TITLE), 0);
    lv_obj_set_style_border_width(rule, 0, 0);
    lv_obj_set_style_radius(rule, 0, 0);
    lv_obj_set_scrollable(rule, false);
  }
  return title;
}

lv_obj_t *ui_make_screen() {
  lv_obj_t *screen = lv_obj_create(nullptr);
  lv_obj_set_style_bg_color(screen, lv_color_hex(UI_COLOR_BG), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
  lv_obj_set_scrollable(screen, false);
  return screen;
}