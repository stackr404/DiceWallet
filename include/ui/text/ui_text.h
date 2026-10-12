#pragma once

#include <lvgl.h>

extern const lv_font_t custom_cyrillic_14;
extern const lv_font_t custom_zh_16;
extern const lv_font_t custom_ja_16;
extern const lv_font_t custom_ko_16;
extern const lv_font_t custom_eu_16;

enum ui_language {
  UI_LANG_EN = 0,
  UI_LANG_FR,
  UI_LANG_DE,
  UI_LANG_PL,
  UI_LANG_SV,
  UI_LANG_NL,
  UI_LANG_RU,
  UI_LANG_IT,
  UI_LANG_ZH,
  UI_LANG_JA,
  UI_LANG_KO,
  UI_LANG_ES,
  UI_LANG_PT
};

void ui_text_set_language(ui_language language);
const char *ui_text_translate(const char *english);
const lv_font_t *ui_font_for(int size);

#define TR(s) ui_text_translate(s)
#define UI_FONT(size) ui_font_for(size)
