/**
 * @file lv_conf.h
 * Minimal LVGL 9 config for the ESP32-2432S028 (240x320).
 * Place this file in the PlatformIO `include/` folder.
 */
#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

#define LV_COLOR_FORMAT_DEFAULT LV_COLOR_FORMAT_RGB565
#define LV_USE_STDLIB_MALLOC LV_STDLIB_BUILTIN
#define LV_USE_STDLIB_STRING LV_STDLIB_BUILTIN
#define LV_USE_STDLIB_SPRINTF LV_STDLIB_BUILTIN

#define LV_DEF_REFR_PERIOD 33
#define LV_DPI_DEF 130

#define LV_USE_OS LV_OS_NONE
#define LV_DRAW_SW_DRAW_UNIT_CNT 1

#define LV_USE_LOG 0
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_22 1
#define LV_FONT_SOURCE_HAN_SANS_SC_16_CJK 1

#define LV_USE_LABEL 1
#define LV_USE_BUTTON 1
#define LV_USE_BAR 1
#define LV_FONT_UNSCII_8 1
#define LV_USE_QRCODE 1

#endif
