#pragma once

#include <lvgl.h>

void ui_screen_replace(lv_obj_t *next);
// Zero RAM-backed label and textarea text before the screen is deleted.
void ui_wipe_screen_text(lv_obj_t *screen);
