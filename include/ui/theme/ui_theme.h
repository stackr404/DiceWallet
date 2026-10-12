#pragma once

#include <stdint.h>

#define UI_RGB(r, g, b) \
  ((((uint32_t)(r) & 0xFF) << 16) | (((uint32_t)(g) & 0xFF) << 8) | ((uint32_t)(b) & 0xFF))

#define UI_COLOR_BG       UI_RGB(18, 20, 26)
#define UI_COLOR_TITLE    UI_RGB(232, 200, 114)
#define UI_COLOR_TEXT     UI_RGB(244, 241, 234)
#define UI_COLOR_MUTED    UI_RGB(154, 160, 173)
#define UI_COLOR_BUTTON   UI_RGB(43, 47, 58)
#define UI_COLOR_PRESSED  UI_RGB(61, 107, 79)

#define UI_COLOR_SUCCESS  UI_RGB(47, 158, 68)
#define UI_COLOR_WARNING  UI_RGB(230, 119, 0)
#define UI_COLOR_ERROR    UI_RGB(224, 49, 49)

// For bar graph displaying die rolls
#define UI_COLOR_FACE_1   UI_RGB(76, 110, 245)
#define UI_COLOR_FACE_2   UI_RGB(18, 184, 134)
#define UI_COLOR_FACE_3   UI_RGB(250, 176, 5)
#define UI_COLOR_FACE_4   UI_RGB(253, 126, 20)
#define UI_COLOR_FACE_5   UI_RGB(224, 49, 49)
#define UI_COLOR_FACE_6   UI_RGB(174, 62, 201)

static const uint32_t UI_COLOR_FACES[6] = {
    UI_COLOR_FACE_1,
    UI_COLOR_FACE_2,
    UI_COLOR_FACE_3,
    UI_COLOR_FACE_4,
    UI_COLOR_FACE_5,
    UI_COLOR_FACE_6,
};

#define UI_SCREEN_W 240
#define UI_SCREEN_H 320

#define UI_TITLE_FONT_SIZE 18
#define UI_TITLE_Y 12
#define UI_TITLE_RULE_Y 40
#define UI_TITLE_RULE_WIDTH 180

#define UI_BUTTON_FULL_WIDTH 200
#define UI_BUTTON_HALF_WIDTH 100
#define UI_BUTTON_HEIGHT 37
#define UI_BUTTON_FONT_SIZE 14
#define UI_BUTTON_BOTTOM_ALIGN LV_ALIGN_BOTTOM_MID
#define UI_BUTTON_BOTTOM_Y_OFFSET -12