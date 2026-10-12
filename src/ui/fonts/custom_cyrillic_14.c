/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --stride 1 --align 1 --font Roboto_Condensed-Medium.ttf --range 32-127,1024-1279 --format lvgl -o custom_cyrillic_14.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef CUSTOM_CYRILLIC_14
#define CUSTOM_CYRILLIC_14 1
#endif

#if CUSTOM_CYRILLIC_14

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0x3c,

    /* U+0022 "\"" */
    0xb6, 0xd0,

    /* U+0023 "#" */
    0x2c, 0xa2, 0xbf, 0x69, 0x24, 0xbf, 0x51, 0x45,
    0x0,

    /* U+0024 "$" */
    0x10, 0x43, 0x9f, 0x6d, 0xb6, 0xe, 0xf, 0xb6,
    0xdf, 0x38, 0x41, 0x0,

    /* U+0025 "%" */
    0x60, 0x94, 0x94, 0x98, 0x68, 0x18, 0x16, 0x39,
    0x29, 0x69, 0x6,

    /* U+0026 "&" */
    0x70, 0xd8, 0xd8, 0xf8, 0x70, 0x70, 0xf6, 0xde,
    0xde, 0xcc, 0x7e,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x13, 0x66, 0xcc, 0xcc, 0xcc, 0xc4, 0x62, 0x30,

    /* U+0029 ")" */
    0x8c, 0x66, 0x33, 0x33, 0x33, 0x32, 0x64, 0xc0,

    /* U+002A "*" */
    0x21, 0x3e, 0x65, 0x6c,

    /* U+002B "+" */
    0x30, 0xc3, 0xc, 0xfc, 0xc3, 0xc,

    /* U+002C "," */
    0x6d, 0xe0,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x10, 0x84, 0x62, 0x11, 0x88, 0x42, 0x31, 0x0,

    /* U+0030 "0" */
    0x79, 0x2c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcd, 0x27,
    0x80,

    /* U+0031 "1" */
    0x1f, 0xb3, 0x33, 0x33, 0x33, 0x30,

    /* U+0032 "2" */
    0x7b, 0x3c, 0xc3, 0xc, 0x63, 0x8c, 0x63, 0x8f,
    0xc0,

    /* U+0033 "3" */
    0x7b, 0x3c, 0xc3, 0x1c, 0xe1, 0xc3, 0xcf, 0x37,
    0x80,

    /* U+0034 "4" */
    0xc, 0x38, 0x71, 0xe2, 0xcd, 0x93, 0x7f, 0xc,
    0x18, 0x30,

    /* U+0035 "5" */
    0x7d, 0xc, 0x30, 0xf9, 0x30, 0xc3, 0xcf, 0x37,
    0x80,

    /* U+0036 "6" */
    0x31, 0x84, 0x30, 0xfb, 0x3c, 0xf3, 0xcd, 0x37,
    0x80,

    /* U+0037 "7" */
    0xfc, 0x30, 0x86, 0x18, 0x43, 0xc, 0x21, 0x86,
    0x0,

    /* U+0038 "8" */
    0x7b, 0x3c, 0xf3, 0xfd, 0xef, 0xf3, 0xcf, 0x37,
    0x80,

    /* U+0039 "9" */
    0x7b, 0x2c, 0xf3, 0xcf, 0x37, 0xc3, 0x8, 0x63,
    0x0,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xf, 0xe0,

    /* U+003C "<" */
    0x9, 0xf9, 0x87, 0xc, 0x20,

    /* U+003D "=" */
    0xf8, 0x1, 0xf0,

    /* U+003E ">" */
    0x87, 0xe, 0x37, 0x62, 0x0,

    /* U+003F "?" */
    0x79, 0x30, 0xc3, 0x18, 0xe3, 0xc, 0x0, 0xc3,
    0x0,

    /* U+0040 "@" */
    0x1e, 0x11, 0x90, 0x48, 0x19, 0xcc, 0xa6, 0xd3,
    0x69, 0xa4, 0xda, 0xa6, 0xc8, 0x6, 0x1, 0xe0,

    /* U+0041 "A" */
    0x18, 0x38, 0x38, 0x28, 0x6c, 0x6c, 0x64, 0x7e,
    0xc6, 0xc2, 0x83,

    /* U+0042 "B" */
    0xfb, 0x3c, 0xf3, 0xcf, 0xcc, 0xf3, 0xcf, 0x3f,
    0x80,

    /* U+0043 "C" */
    0x3c, 0xcf, 0x1e, 0xc, 0x18, 0x30, 0x60, 0xc6,
    0xcc, 0xf0,

    /* U+0044 "D" */
    0xf3, 0x6c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x6f,
    0x0,

    /* U+0045 "E" */
    0xff, 0xc, 0x30, 0xc3, 0xec, 0x30, 0xc3, 0xf,
    0xc0,

    /* U+0046 "F" */
    0xff, 0xc, 0x30, 0xc3, 0xec, 0x30, 0xc3, 0xc,
    0x0,

    /* U+0047 "G" */
    0x3c, 0xdf, 0x1e, 0x3c, 0x18, 0x33, 0xe3, 0xc6,
    0xcc, 0xf0,

    /* U+0048 "H" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xcf, 0x37,
    0x80,

    /* U+004B "K" */
    0xc7, 0x9b, 0x66, 0xcf, 0x1e, 0x3e, 0x6c, 0xcd,
    0x9b, 0x18,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf,
    0xc0,

    /* U+004D "M" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7f, 0x7f, 0xbf, 0x57,
    0xab, 0xdd, 0xe4, 0xf2, 0x60,

    /* U+004E "N" */
    0xc7, 0xcf, 0x9f, 0x3f, 0x7a, 0xf7, 0xe7, 0xcf,
    0x9f, 0x18,

    /* U+004F "O" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0050 "P" */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xff, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0051 "Q" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xd8, 0xf0, 0x30, 0x0,

    /* U+0052 "R" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x2f, 0x34, 0xdb, 0x3c,
    0xc0,

    /* U+0053 "S" */
    0x7b, 0x3c, 0xf0, 0xf1, 0xe1, 0xc3, 0xcf, 0x37,
    0x80,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8d, 0xf0,

    /* U+0056 "V" */
    0xc3, 0x42, 0x66, 0x66, 0x66, 0x24, 0x3c, 0x3c,
    0x18, 0x18, 0x18,

    /* U+0057 "W" */
    0x88, 0xce, 0x77, 0x7b, 0xbd, 0x5e, 0xad, 0x54,
    0xee, 0x77, 0x31, 0x98, 0xc0,

    /* U+0058 "X" */
    0x66, 0xcc, 0x91, 0xe3, 0x83, 0xe, 0x1e, 0x64,
    0xcd, 0x18,

    /* U+0059 "Y" */
    0xc3, 0x66, 0x66, 0x24, 0x3c, 0x3c, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xfc, 0x10, 0x82, 0x10, 0xc2, 0x18, 0x43, 0xf,
    0xc0,

    /* U+005B "[" */
    0xfb, 0x6d, 0xb6, 0xdb, 0x6d, 0xc0,

    /* U+005C "\\" */
    0xc2, 0x18, 0xc2, 0x10, 0xc6, 0x10, 0xc6, 0x10,

    /* U+005D "]" */
    0xed, 0xb6, 0xdb, 0x6d, 0xb7, 0xc0,

    /* U+005E "^" */
    0x21, 0x9c, 0xa5, 0x2c,

    /* U+005F "_" */
    0xf8,

    /* U+0060 "`" */
    0x62,

    /* U+0061 "a" */
    0x76, 0xc6, 0xfd, 0xef, 0x6f,

    /* U+0062 "b" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x3f,
    0x80,

    /* U+0063 "c" */
    0x7b, 0x2c, 0xb0, 0xc3, 0x3c, 0x9c,

    /* U+0064 "d" */
    0xc, 0x30, 0xdf, 0xcf, 0x3c, 0xf3, 0xcf, 0x37,
    0xc0,

    /* U+0065 "e" */
    0x7b, 0x3c, 0xff, 0xc3, 0xc, 0x9e,

    /* U+0066 "f" */
    0x36, 0x6f, 0x66, 0x66, 0x66, 0x60,

    /* U+0067 "g" */
    0x7f, 0x3c, 0xf3, 0xcf, 0x3c, 0xdf, 0xd, 0x37,
    0x80,

    /* U+0068 "h" */
    0xc6, 0x31, 0xed, 0xef, 0x7b, 0xde, 0xf6,

    /* U+0069 "i" */
    0xf3, 0xff, 0xfc,

    /* U+006A "j" */
    0x6c, 0x36, 0xdb, 0x6d, 0xb7, 0x80,

    /* U+006B "k" */
    0xc3, 0xc, 0x32, 0xdb, 0xcf, 0x3c, 0xdb, 0x6c,
    0xc0,

    /* U+006C "l" */
    0xff, 0xff, 0xfc,

    /* U+006D "m" */
    0xf7, 0x6c, 0xf6, 0x7b, 0x3d, 0x9e, 0xcf, 0x67,
    0xb3,

    /* U+006E "n" */
    0xf6, 0xf7, 0xbd, 0xef, 0x7b,

    /* U+006F "o" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x3c, 0xde,

    /* U+0070 "p" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xfe, 0xc3, 0xc,
    0x0,

    /* U+0071 "q" */
    0x7f, 0x3c, 0xf3, 0xcf, 0x3c, 0xdf, 0xc, 0x30,
    0xc0,

    /* U+0072 "r" */
    0xfc, 0xcc, 0xcc, 0xcc,

    /* U+0073 "s" */
    0x76, 0xf1, 0xe7, 0x8f, 0x6e,

    /* U+0074 "t" */
    0x66, 0xf6, 0x66, 0x66, 0x73,

    /* U+0075 "u" */
    0xde, 0xf7, 0xbd, 0xef, 0x6f,

    /* U+0076 "v" */
    0xcb, 0x25, 0x96, 0x71, 0xc3, 0xc,

    /* U+0077 "w" */
    0xdb, 0xdb, 0xdb, 0x5a, 0x7e, 0x7e, 0x66, 0x66,

    /* U+0078 "x" */
    0x4d, 0xa3, 0x8c, 0x31, 0xe6, 0x93,

    /* U+0079 "y" */
    0x4d, 0x36, 0x9a, 0x38, 0xe3, 0xc, 0x10, 0xc6,
    0x0,

    /* U+007A "z" */
    0xf8, 0xcc, 0x46, 0x22, 0x1f,

    /* U+007B "{" */
    0x13, 0x66, 0x66, 0xec, 0xe6, 0x66, 0x66, 0x10,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0x8c, 0x66, 0x66, 0x63, 0x76, 0x66, 0x6c, 0x80,

    /* U+007E "~" */
    0x65, 0x2a, 0x70,

    /* U+0400 "Ѐ" */
    0x60, 0x81, 0x3f, 0xc3, 0xc, 0x30, 0xfb, 0xc,
    0x30, 0xc3, 0xf0,

    /* U+0401 "Ё" */
    0xd8, 0x3f, 0x8c, 0x63, 0x1f, 0xc6, 0x31, 0x8f,
    0x80,

    /* U+0402 "Ђ" */
    0xfc, 0x30, 0x30, 0x30, 0x30, 0x3e, 0x33, 0x33,
    0x33, 0x33, 0x36,

    /* U+0403 "Ѓ" */
    0x8, 0x63, 0x3f, 0xc3, 0xc, 0x30, 0xc3, 0xc,
    0x30, 0xc3, 0x0,

    /* U+0404 "Є" */
    0x38, 0xdb, 0x16, 0x3c, 0x1e, 0x30, 0x63, 0xc4,
    0xc8, 0xe0,

    /* U+0405 "Ѕ" */
    0x7b, 0x3c, 0xf0, 0xf1, 0xe3, 0xc3, 0xcf, 0x37,
    0x80,

    /* U+0406 "І" */
    0xff, 0xff, 0xfc,

    /* U+0407 "Ї" */
    0xd8, 0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6,
    0x0,

    /* U+0408 "Ј" */
    0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xcf, 0x37,
    0x80,

    /* U+0409 "Љ" */
    0x3f, 0x1, 0x98, 0xc, 0xc0, 0x66, 0x3, 0x3f,
    0x19, 0x98, 0xcc, 0x66, 0x63, 0x33, 0x1b, 0x19,
    0xb8, 0xfc,

    /* U+040A "Њ" */
    0xc6, 0xc, 0x60, 0xc6, 0xc, 0x60, 0xc6, 0xf,
    0xfe, 0xc6, 0x7c, 0x63, 0xc6, 0x3c, 0x63, 0xc7,
    0xe0,

    /* U+040B "Ћ" */
    0xfc, 0x30, 0x30, 0x30, 0x30, 0x3e, 0x33, 0x33,
    0x33, 0x33, 0x33,

    /* U+040C "Ќ" */
    0x18, 0x30, 0xc6, 0x3c, 0xdb, 0x36, 0x78, 0xf1,
    0xf3, 0x66, 0x6c, 0xd8, 0xc0,

    /* U+040D "Ѝ" */
    0x60, 0x60, 0x46, 0x3c, 0xf9, 0xf3, 0xef, 0xd7,
    0xef, 0x9f, 0x3e, 0x78, 0xc0,

    /* U+040E "Ў" */
    0x4c, 0x90, 0xe6, 0x3c, 0xc9, 0x9b, 0x34, 0x38,
    0x70, 0xc0, 0x83, 0xc, 0x0,

    /* U+040F "Џ" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0xf9, 0x83, 0x6, 0x0,

    /* U+0410 "А" */
    0x18, 0x38, 0x38, 0x28, 0x6c, 0x6c, 0x64, 0x7e,
    0xc6, 0xc2, 0x83,

    /* U+0411 "Б" */
    0xfb, 0xc, 0x30, 0xc3, 0xec, 0xf3, 0xcf, 0x3f,
    0x80,

    /* U+0412 "В" */
    0xfb, 0x3c, 0xf3, 0xcf, 0xcc, 0xf3, 0xcf, 0x3f,
    0x80,

    /* U+0413 "Г" */
    0xff, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xc,
    0x0,

    /* U+0414 "Д" */
    0x3f, 0x19, 0x8c, 0xc6, 0x63, 0x31, 0x98, 0xcc,
    0x66, 0x23, 0x31, 0xbf, 0xf8, 0x3c, 0x1e, 0xc,

    /* U+0415 "Е" */
    0xff, 0xc, 0x30, 0xc3, 0xec, 0x30, 0xc3, 0xf,
    0xc0,

    /* U+0416 "Ж" */
    0x46, 0x66, 0x66, 0x26, 0x43, 0x6c, 0x16, 0x81,
    0xf8, 0x36, 0xc3, 0x6c, 0x66, 0x66, 0x66, 0xc6,
    0x30,

    /* U+0417 "З" */
    0x3c, 0xcf, 0x18, 0x30, 0xe3, 0x83, 0x83, 0x46,
    0x8c, 0xf0,

    /* U+0418 "И" */
    0xc7, 0x9f, 0x3e, 0x7d, 0xfa, 0xfd, 0xf3, 0xe7,
    0xcf, 0x18,

    /* U+0419 "Й" */
    0x6c, 0x50, 0xe6, 0x3c, 0xf9, 0xf3, 0xef, 0xd7,
    0xef, 0x9f, 0x3e, 0x78, 0xc0,

    /* U+041A "К" */
    0xc7, 0x9b, 0x36, 0xcd, 0x1e, 0x36, 0x64, 0xcd,
    0x8b, 0x18,

    /* U+041B "Л" */
    0x3f, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    0x33, 0xe3, 0xe3,

    /* U+041C "М" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7f, 0x7f, 0xbf, 0x57,
    0xab, 0xdd, 0xe4, 0xf2, 0x60,

    /* U+041D "Н" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+041E "О" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+041F "П" */
    0xff, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0420 "Р" */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xff, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0421 "С" */
    0x3c, 0xcf, 0x1e, 0xc, 0x18, 0x30, 0x60, 0xc6,
    0xcc, 0xf0,

    /* U+0422 "Т" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0423 "У" */
    0xc5, 0x99, 0x33, 0x46, 0x87, 0xe, 0x18, 0x30,
    0x61, 0x80,

    /* U+0424 "Ф" */
    0x18, 0x18, 0x3c, 0x7e, 0xdb, 0xdb, 0xdb, 0xdb,
    0x7e, 0x3c, 0x18, 0x18,

    /* U+0425 "Х" */
    0x66, 0xcc, 0x91, 0xe3, 0x83, 0xe, 0x1e, 0x64,
    0xcd, 0x18,

    /* U+0426 "Ц" */
    0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6,
    0xc6, 0xc6, 0xff, 0x3, 0x3, 0x3,

    /* U+0427 "Ч" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x6,
    0xc, 0x18,

    /* U+0428 "Ш" */
    0xcc, 0xf3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33, 0xcc, 0xf3, 0x3f, 0xfc,

    /* U+0429 "Щ" */
    0xcc, 0xd9, 0x9b, 0x33, 0x66, 0x6c, 0xcd, 0x99,
    0xb3, 0x36, 0x66, 0xcc, 0xd9, 0x9b, 0xff, 0x80,
    0x30, 0x6, 0x0, 0xc0,

    /* U+042A "Ъ" */
    0xf0, 0x30, 0x30, 0x30, 0x30, 0x3e, 0x33, 0x33,
    0x33, 0x33, 0x3e,

    /* U+042B "Ы" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xcf, 0x37,
    0x9b, 0xcd, 0xe6, 0xfe, 0x60,

    /* U+042C "Ь" */
    0xc3, 0xc, 0x30, 0xc3, 0xec, 0xf3, 0xcf, 0x3f,
    0x80,

    /* U+042D "Э" */
    0x38, 0x9b, 0x1e, 0x30, 0x67, 0xc1, 0xe3, 0xc6,
    0x99, 0xe0,

    /* U+042E "Ю" */
    0xcf, 0x36, 0x6f, 0xf, 0xc3, 0xf0, 0xfc, 0x3f,
    0xf, 0xc3, 0xf0, 0xf6, 0x6c, 0xf0,

    /* U+042F "Я" */
    0x7f, 0x3c, 0xf3, 0xcd, 0x33, 0xdb, 0x6f, 0x3c,
    0xc0,

    /* U+0430 "а" */
    0x76, 0xc6, 0xfd, 0xef, 0x6f,

    /* U+0431 "б" */
    0x8, 0x67, 0x90, 0x82, 0xec, 0xf3, 0xcf, 0x3c,
    0xde,

    /* U+0432 "в" */
    0xfb, 0x3c, 0xf2, 0xfb, 0x3c, 0xfe,

    /* U+0433 "г" */
    0xfe, 0x31, 0x8c, 0x63, 0x18,

    /* U+0434 "д" */
    0x7c, 0xd9, 0xb3, 0x66, 0xcd, 0x93, 0x7f, 0xc7,
    0x8f, 0x18,

    /* U+0435 "е" */
    0x7b, 0x3c, 0xff, 0xc3, 0xc, 0x9e,

    /* U+0436 "ж" */
    0xcc, 0xdb, 0x66, 0xd8, 0xb4, 0x3f, 0xb, 0x66,
    0xdb, 0x33,

    /* U+0437 "з" */
    0x79, 0x30, 0xce, 0x1c, 0x34, 0xde,

    /* U+0438 "и" */
    0xcf, 0x7d, 0xf7, 0xef, 0xbe, 0xf3,

    /* U+0439 "й" */
    0x49, 0xe0, 0x33, 0xdf, 0x7d, 0xfb, 0xef, 0xbc,
    0xc0,

    /* U+043A "к" */
    0xcf, 0x6d, 0xb4, 0xf3, 0x6d, 0xb3,

    /* U+043B "л" */
    0x7d, 0xb6, 0xdb, 0x6d, 0xbe, 0xf3,

    /* U+043C "м" */
    0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xdb, 0xdb, 0xdb,

    /* U+043D "н" */
    0xcf, 0x3c, 0xf3, 0xff, 0x3c, 0xf3,

    /* U+043E "о" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x3c, 0xde,

    /* U+043F "п" */
    0xff, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3,

    /* U+0440 "р" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xfe, 0xc3, 0xc,
    0x0,

    /* U+0441 "с" */
    0x7b, 0x2c, 0xb0, 0xc3, 0x3c, 0x9c,

    /* U+0442 "т" */
    0xfc, 0xc3, 0xc, 0x30, 0xc3, 0xc,

    /* U+0443 "у" */
    0x4d, 0x36, 0x9a, 0x38, 0xe3, 0xc, 0x10, 0xc6,
    0x0,

    /* U+0444 "ф" */
    0x10, 0x10, 0x10, 0x7e, 0xd7, 0xd3, 0xd3, 0xd3,
    0xd3, 0xd7, 0x7e, 0x10, 0x10, 0x10,

    /* U+0445 "х" */
    0x4d, 0xa3, 0x8c, 0x31, 0xe6, 0x93,

    /* U+0446 "ц" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xff, 0xc, 0x30,
    0xc0,

    /* U+0447 "ч" */
    0xde, 0xf7, 0xb7, 0x8c, 0x63,

    /* U+0448 "ш" */
    0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xff,

    /* U+0449 "щ" */
    0xdb, 0x36, 0xcd, 0xb3, 0x6c, 0xdb, 0x36, 0xcd,
    0xb3, 0xff, 0x0, 0xc0, 0x30, 0xc,

    /* U+044A "ъ" */
    0xf0, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x33, 0x3e,

    /* U+044B "ы" */
    0xc3, 0xc3, 0xc3, 0xfb, 0xcf, 0xcf, 0xcf, 0xfb,

    /* U+044C "ь" */
    0xc3, 0xc, 0x3e, 0xcf, 0x3c, 0xfe,

    /* U+044D "э" */
    0x73, 0x20, 0xcf, 0xf, 0x3d, 0x9c,

    /* U+044E "ю" */
    0xcf, 0x64, 0xb6, 0x7a, 0x3f, 0x1e, 0xcf, 0x25,
    0x9e,

    /* U+044F "я" */
    0x7f, 0x3c, 0xf3, 0x7d, 0xb4, 0xf3,

    /* U+0450 "ѐ" */
    0xe1, 0x82, 0x0, 0x7b, 0x3c, 0xff, 0xc3, 0xc,
    0x9e,

    /* U+0451 "ё" */
    0xd8, 0x0, 0x1e, 0xcf, 0x3f, 0xf0, 0xc3, 0x27,
    0x80,

    /* U+0452 "ђ" */
    0x63, 0xc6, 0x1e, 0x6d, 0xb6, 0xdb, 0x6d, 0xb6,
    0xc3, 0xc, 0x60,

    /* U+0453 "ѓ" */
    0x31, 0x1, 0xfc, 0x63, 0x18, 0xc6, 0x30,

    /* U+0454 "є" */
    0x7b, 0x2c, 0x3c, 0xc3, 0x2c, 0x9c,

    /* U+0455 "ѕ" */
    0x76, 0xf1, 0xe7, 0x8f, 0x6e,

    /* U+0456 "і" */
    0xf3, 0xff, 0xfc,

    /* U+0457 "ї" */
    0xd8, 0x0, 0xc6, 0x31, 0x8c, 0x63, 0x18,

    /* U+0458 "ј" */
    0x6c, 0x36, 0xdb, 0x6d, 0xb7, 0x80,

    /* U+0459 "љ" */
    0x7c, 0x1b, 0x6, 0xc1, 0xbe, 0x6c, 0xdb, 0x36,
    0xcf, 0x3e,

    /* U+045A "њ" */
    0xcc, 0x33, 0xc, 0xc3, 0xfe, 0xcc, 0xf3, 0x3c,
    0xcf, 0x3e,

    /* U+045B "ћ" */
    0x63, 0xc6, 0x1e, 0x6d, 0xb6, 0xdb, 0x6d, 0xb6,
    0xc0,

    /* U+045C "ќ" */
    0x18, 0xc0, 0x33, 0xdb, 0x6d, 0x3c, 0xdb, 0x6c,
    0xc0,

    /* U+045D "ѝ" */
    0x60, 0xc0, 0x33, 0xdf, 0x7d, 0xfb, 0xef, 0xbc,
    0xc0,

    /* U+045E "ў" */
    0x68, 0xe0, 0x13, 0x4d, 0xa6, 0x8e, 0x38, 0xc3,
    0xc, 0x21, 0x80,

    /* U+045F "џ" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xff, 0x30, 0xc3,
    0x0,

    /* U+0460 "Ѡ" */
    0xd8, 0xf6, 0x3d, 0x8f, 0x63, 0xd8, 0xf6, 0x3d,
    0x8f, 0x63, 0xd8, 0xf7, 0x37, 0x70,

    /* U+0461 "ѡ" */
    0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e,

    /* U+0462 "Ѣ" */
    0x60, 0xc3, 0xc3, 0x6, 0xf, 0x99, 0xb3, 0x66,
    0xcd, 0xf0,

    /* U+0463 "ѣ" */
    0x60, 0xc1, 0x87, 0x86, 0xc, 0x18, 0x3e, 0x66,
    0xcd, 0x9b, 0xe0,

    /* U+0464 "Ѥ" */
    0xcf, 0x36, 0x6f, 0xb, 0xc2, 0xf0, 0x3f, 0x8f,
    0x3, 0xc0, 0xf0, 0xb6, 0x6c, 0xf0,

    /* U+0465 "ѥ" */
    0xde, 0xd3, 0xf3, 0xfc, 0xf0, 0xf3, 0xd3, 0xde,

    /* U+0466 "Ѧ" */
    0x18, 0x1c, 0x3c, 0x3c, 0x34, 0x66, 0x66, 0x7e,
    0x5a, 0xdb, 0xdb,

    /* U+0467 "ѧ" */
    0x10, 0x70, 0xa1, 0x46, 0xcf, 0x95, 0x2a,

    /* U+0468 "Ѩ" */
    0xc6, 0x31, 0xcc, 0xf3, 0x3c, 0xcd, 0x33, 0x6c,
    0x9b, 0xfe, 0xde, 0xb7, 0xbd, 0xec,

    /* U+0469 "ѩ" */
    0xc4, 0x67, 0x32, 0x99, 0x4d, 0xb7, 0xfb, 0x55,
    0xea,

    /* U+046A "Ѫ" */
    0x7f, 0x19, 0x8c, 0x83, 0xc1, 0xc3, 0xfb, 0x37,
    0x9b, 0xcd, 0xe6, 0xf3, 0x60,

    /* U+046B "ѫ" */
    0x7e, 0x24, 0x3c, 0x3c, 0x7e, 0xdb, 0xdb, 0xdb,

    /* U+046C "Ѭ" */
    0xcf, 0xec, 0x66, 0xc6, 0x4c, 0x3c, 0xc3, 0x8f,
    0xfe, 0xd9, 0xbd, 0x9b, 0xd9, 0xbd, 0x9b, 0xd9,
    0xb0,

    /* U+046D "ѭ" */
    0xcf, 0xd8, 0x93, 0x1e, 0x63, 0xcf, 0xfd, 0xb6,
    0xf6, 0xde, 0xdb,

    /* U+046E "Ѯ" */
    0x51, 0x0, 0xe1, 0x8c, 0x67, 0x31, 0xc6, 0x31,
    0xfb, 0x18, 0x40,

    /* U+046F "ѯ" */
    0xcb, 0x80, 0x7, 0x4, 0x66, 0x18, 0x42, 0xec,
    0x61, 0x0,

    /* U+0470 "Ѱ" */
    0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e, 0x3c,
    0x18, 0x18, 0x18,

    /* U+0471 "ѱ" */
    0xda, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e, 0x3c,
    0x18, 0x18, 0x18, 0x18,

    /* U+0472 "Ѳ" */
    0x38, 0xdb, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0473 "ѳ" */
    0x79, 0x2c, 0xff, 0xcf, 0x34, 0x9e,

    /* U+0474 "Ѵ" */
    0xc3, 0x8b, 0x12, 0x24, 0xcd, 0x1a, 0x14, 0x38,
    0x70, 0xc0,

    /* U+0475 "ѵ" */
    0xcd, 0x34, 0x9e, 0x78, 0xc3, 0xc,

    /* U+0476 "Ѷ" */
    0x50, 0xf3, 0xe, 0x2c, 0x48, 0x93, 0x34, 0x68,
    0x50, 0xe1, 0xc3, 0x0,

    /* U+0477 "ѷ" */
    0xd1, 0xe0, 0x33, 0x4d, 0x27, 0x9e, 0x30, 0xc3,
    0x0,

    /* U+0478 "Ѹ" */
    0x38, 0x1, 0xb0, 0xc, 0x60, 0x31, 0xb2, 0xc6,
    0xcb, 0x19, 0x6c, 0x65, 0xb1, 0x9c, 0xc6, 0x71,
    0xb0, 0xc3, 0x83, 0x0, 0x8, 0x0, 0x20, 0x3,
    0x0,

    /* U+0479 "ѹ" */
    0x79, 0x3c, 0xdb, 0xcd, 0xac, 0xda, 0xcc, 0xec,
    0xce, 0xcc, 0xc7, 0x84, 0x0, 0x40, 0xc, 0x1,
    0x80,

    /* U+047A "Ѻ" */
    0x10, 0x71, 0xf6, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8d, 0xf1, 0xc1, 0x0,

    /* U+047B "ѻ" */
    0x21, 0xe6, 0xb3, 0xcf, 0x3c, 0xda, 0x78, 0x80,

    /* U+047C "Ѽ" */
    0x18, 0xb, 0x1, 0xd, 0x2c, 0x1e, 0xf, 0x7,
    0x83, 0xcd, 0xe6, 0xf3, 0x79, 0xbc, 0xdb, 0xd8,

    /* U+047D "ѽ" */
    0x18, 0x58, 0x2, 0x6c, 0x58, 0x74, 0xe9, 0xd3,
    0xa9, 0xb0,

    /* U+047E "Ѿ" */
    0x3e, 0x6, 0xd, 0x8f, 0x63, 0xd8, 0xf6, 0x3d,
    0x8f, 0x63, 0xd8, 0xf6, 0x3d, 0x8f, 0x73, 0x77,
    0x0,

    /* U+047F "ѿ" */
    0x3c, 0x18, 0x0, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xdb, 0xdb, 0x7e,

    /* U+0480 "Ҁ" */
    0x3c, 0xcf, 0x1e, 0xc, 0x18, 0x30, 0x60, 0xc0,
    0x81, 0xc1, 0x83, 0x6, 0x0,

    /* U+0481 "ҁ" */
    0x73, 0x2c, 0xb0, 0xc3, 0xc, 0x1c, 0x30, 0xc3,
    0x0,

    /* U+0482 "҂" */
    0x8, 0x23, 0x6, 0x1e, 0x86, 0x1c, 0x52, 0x0,

    /* U+0483 "҃" */
    0x1f, 0xe0,

    /* U+0484 "҄" */
    0x79,

    /* U+0485 "҅" */
    0xc0,

    /* U+0486 "҆" */
    0xc0,

    /* U+0488 "҈" */
    0x6, 0x0, 0x0, 0x1c, 0x18, 0x0, 0x0, 0x0,
    0x60, 0xe, 0x80, 0xa0, 0x0, 0x0, 0x3, 0x3,
    0x14, 0x14, 0xc, 0x0, 0x50, 0x0,

    /* U+0489 "҉" */
    0x2, 0x0, 0x10, 0x8, 0x8, 0x40, 0x0, 0x0,
    0x0, 0x3, 0x0, 0x60, 0x0, 0x0, 0x0, 0x0,
    0xc, 0x8, 0x4, 0x40, 0x20, 0x0,

    /* U+048A "Ҋ" */
    0x24, 0x28, 0x38, 0xc6, 0xce, 0xce, 0xce, 0xde,
    0xd6, 0xf6, 0xe6, 0xe6, 0xe6, 0xc7, 0x3, 0x3,
    0x2,

    /* U+048B "ҋ" */
    0x6c, 0x70, 0x6, 0x6d, 0xdb, 0xb7, 0x76, 0xed,
    0xdb, 0x38, 0x30, 0x60, 0x80,

    /* U+048C "Ҍ" */
    0x60, 0xc3, 0xc3, 0x6, 0xf, 0x99, 0xb3, 0x66,
    0xcd, 0xf0,

    /* U+048D "ҍ" */
    0x61, 0xe1, 0x83, 0x6, 0xc, 0x18, 0x3e, 0x66,
    0xcd, 0x9b, 0xe0,

    /* U+048E "Ҏ" */
    0xfd, 0x9b, 0x1e, 0x3c, 0xf9, 0xff, 0xe0, 0xc1,
    0x83, 0x0,

    /* U+048F "ҏ" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x7c, 0xff, 0xc3, 0xc,
    0x0,

    /* U+0490 "Ґ" */
    0xc, 0x3f, 0xf0, 0xc3, 0xc, 0x30, 0xc3, 0xc,
    0x30, 0xc0,

    /* U+0491 "ґ" */
    0x18, 0xff, 0x8c, 0x63, 0x18, 0xc6, 0x0,

    /* U+0492 "Ғ" */
    0x7e, 0xc1, 0x83, 0x6, 0x1e, 0x18, 0x30, 0x60,
    0xc1, 0x80,

    /* U+0493 "ғ" */
    0x7d, 0x86, 0x18, 0xf1, 0x86, 0x18,

    /* U+0494 "Ҕ" */
    0xfb, 0xc, 0x30, 0xc3, 0xed, 0xb3, 0xcf, 0x3c,
    0xc2, 0x18,

    /* U+0495 "ҕ" */
    0xf6, 0x31, 0xed, 0xef, 0x7b, 0x18, 0x80,

    /* U+0496 "Җ" */
    0x46, 0x66, 0x64, 0x26, 0xc3, 0x68, 0x16, 0x81,
    0xf8, 0x36, 0x83, 0x6c, 0x66, 0xc6, 0x64, 0xc6,
    0x70, 0x3, 0x0, 0x30, 0x3,

    /* U+0497 "җ" */
    0xcd, 0x9b, 0x46, 0xd0, 0xb4, 0x3e, 0xb, 0x46,
    0xd3, 0x37, 0x0, 0xc0, 0x30, 0xc,

    /* U+0498 "Ҙ" */
    0x7b, 0x3c, 0xc3, 0x1c, 0xe1, 0xc3, 0xcf, 0xf7,
    0x8c, 0x30, 0xc0,

    /* U+0499 "ҙ" */
    0x76, 0x46, 0x60, 0xe7, 0xee, 0x31, 0x8c,

    /* U+049A "Қ" */
    0xc6, 0xcc, 0xcc, 0xd8, 0xd0, 0xf0, 0xd8, 0xd8,
    0xcc, 0xcc, 0xc7, 0x3, 0x3, 0x3,

    /* U+049B "қ" */
    0xcd, 0xb3, 0x66, 0x8f, 0x1a, 0x36, 0x67, 0x6,
    0xc, 0x18,

    /* U+049C "Ҝ" */
    0xc7, 0x9b, 0x37, 0x4f, 0x9f, 0x3e, 0x74, 0xcd,
    0x9b, 0x18,

    /* U+049D "ҝ" */
    0xcf, 0x3e, 0xbe, 0xf3, 0xec, 0xf3,

    /* U+049E "Ҟ" */
    0x63, 0x66, 0xf6, 0x6c, 0x68, 0x78, 0x6c, 0x64,
    0x66, 0x62, 0x63,

    /* U+049F "ҟ" */
    0x61, 0xe1, 0x83, 0x26, 0xcd, 0x1e, 0x34, 0x6c,
    0xc9, 0x98,

    /* U+04A0 "Ҡ" */
    0xf8, 0xc6, 0x61, 0x98, 0x6c, 0x1a, 0x7, 0x81,
    0xb0, 0x64, 0x19, 0x86, 0x21, 0x8c,

    /* U+04A1 "ҡ" */
    0xf9, 0x8d, 0x86, 0xc3, 0x41, 0xe0, 0xd8, 0x6c,
    0x33,

    /* U+04A2 "Ң" */
    0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6,
    0xc6, 0xc6, 0xc7, 0x3, 0x3, 0x3,

    /* U+04A3 "ң" */
    0xcd, 0x9b, 0x36, 0x6f, 0xd9, 0xb3, 0x67, 0x6,
    0xc, 0x18,

    /* U+04A4 "Ҥ" */
    0xc7, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x3f, 0x8c,
    0x63, 0x18, 0xc6, 0x31, 0x8c, 0x60,

    /* U+04A5 "ҥ" */
    0xcf, 0xcc, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0xcc,

    /* U+04A6 "Ҧ" */
    0xfe, 0x18, 0xc3, 0x18, 0x63, 0xc, 0x61, 0x8f,
    0x31, 0xb6, 0x33, 0xc6, 0x78, 0xcf, 0x19, 0x80,
    0x20, 0xc,

    /* U+04A7 "ҧ" */
    0xfc, 0x66, 0x33, 0x19, 0xec, 0xde, 0x6f, 0x37,
    0x9b, 0x1, 0x80, 0x80,

    /* U+04A8 "Ҩ" */
    0x6e, 0x5a, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xce, 0x6e, 0x3f,

    /* U+04A9 "ҩ" */
    0x5d, 0xef, 0xdf, 0xbf, 0x7e, 0xdf, 0x1f,

    /* U+04AA "Ҫ" */
    0x79, 0x3c, 0xf0, 0xc3, 0xc, 0x33, 0xcd, 0xf7,
    0x8c, 0x30, 0xc0,

    /* U+04AB "ҫ" */
    0x7b, 0x2c, 0xb0, 0xc3, 0x2f, 0x9c, 0x30, 0xc3,
    0x0,

    /* U+04AC "Ҭ" */
    0xfe, 0x30, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30, 0x70, 0x60, 0xc1, 0x80,

    /* U+04AD "ҭ" */
    0xfc, 0xc3, 0xc, 0x30, 0xc3, 0xe, 0x18, 0x61,
    0x80,

    /* U+04AE "Ү" */
    0xc3, 0x66, 0x66, 0x24, 0x3c, 0x3c, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+04AF "ү" */
    0xcf, 0x34, 0x9e, 0x79, 0xe3, 0xc, 0x30, 0xc3,
    0x0,

    /* U+04B0 "Ұ" */
    0xc3, 0x66, 0x66, 0x24, 0x3c, 0x3c, 0x3c, 0x18,
    0x18, 0x18, 0x18,

    /* U+04B1 "ұ" */
    0xcf, 0x34, 0x9e, 0x79, 0xe3, 0x1e, 0x30, 0xc3,
    0x0,

    /* U+04B2 "Ҳ" */
    0xc6, 0x66, 0x6c, 0x2c, 0x38, 0x18, 0x38, 0x3c,
    0x6c, 0x66, 0xc7, 0x3, 0x3, 0x3,

    /* U+04B3 "ҳ" */
    0xdb, 0x67, 0x1c, 0x61, 0xcd, 0xb7, 0xc, 0x30,
    0xc0,

    /* U+04B4 "Ҵ" */
    0xfd, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c, 0x63,
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0xfc, 0x3, 0x0,
    0xc0, 0x30,

    /* U+04B5 "ҵ" */
    0xf6, 0xcd, 0x9b, 0x36, 0x6c, 0xd9, 0xbf, 0x6,
    0xc, 0x18,

    /* U+04B6 "Ҷ" */
    0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7e, 0x6,
    0x6, 0x6, 0x7, 0x3, 0x3, 0x3,

    /* U+04B7 "ҷ" */
    0xd9, 0xb3, 0x66, 0xc7, 0x83, 0x6, 0xf, 0x6,
    0xc, 0x18,

    /* U+04B8 "Ҹ" */
    0xc7, 0x8f, 0x1e, 0xbd, 0x7a, 0xdf, 0x8b, 0x16,
    0xc, 0x18,

    /* U+04B9 "ҹ" */
    0xde, 0xff, 0xf7, 0x9c, 0x63,

    /* U+04BA "Һ" */
    0xc1, 0x83, 0x6, 0xc, 0x1f, 0xb1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+04BB "һ" */
    0xc6, 0x31, 0xed, 0xef, 0x7b, 0xde, 0xf6,

    /* U+04BC "Ҽ" */
    0xe, 0xd, 0x8c, 0x76, 0x3f, 0x1b, 0xfc, 0xc0,
    0x60, 0x30, 0xc, 0x3, 0xc0,

    /* U+04BD "ҽ" */
    0x3d, 0x4f, 0x9b, 0xf6, 0xc, 0xc, 0x8e,

    /* U+04BE "Ҿ" */
    0xe, 0xd, 0x8c, 0x76, 0x3f, 0x1b, 0xfc, 0xc0,
    0x60, 0x38, 0xf, 0x83, 0xc0, 0xc0, 0x60, 0x30,

    /* U+04BF "ҿ" */
    0x3d, 0x4f, 0x9b, 0xf6, 0xc, 0xf, 0x8e, 0x18,
    0x30, 0x60,

    /* U+04C0 "Ӏ" */
    0xff, 0xff, 0xfc,

    /* U+04C1 "Ӂ" */
    0x19, 0x1, 0x20, 0x38, 0x63, 0x36, 0x66, 0x4d,
    0x8d, 0xb0, 0xb4, 0x1f, 0x86, 0xd0, 0xdb, 0x33,
    0x26, 0x67, 0x8c, 0xc0,

    /* U+04C2 "ӂ" */
    0x12, 0xe, 0x0, 0x19, 0xb6, 0xdb, 0x68, 0xb4,
    0x7e, 0x6d, 0x36, 0xf3, 0x60,

    /* U+04C3 "Ӄ" */
    0xcf, 0x9b, 0x26, 0xcd, 0x1f, 0x33, 0x63, 0xc7,
    0x8f, 0x18, 0x20, 0x80,

    /* U+04C4 "ӄ" */
    0xcf, 0x6d, 0xb4, 0xfb, 0x3c, 0xf3, 0x1c, 0x60,

    /* U+04C5 "Ӆ" */
    0x3f, 0x19, 0x8c, 0xc6, 0x63, 0x31, 0x98, 0xcc,
    0x66, 0x33, 0x71, 0xb8, 0xe0, 0x30, 0x18, 0x8,

    /* U+04C6 "ӆ" */
    0x7c, 0xd9, 0xb3, 0x66, 0xcd, 0xbb, 0x67, 0x6,
    0xc, 0x10,

    /* U+04C7 "Ӈ" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18, 0x30, 0x61, 0x80,

    /* U+04C8 "ӈ" */
    0xcf, 0x3c, 0xff, 0xcf, 0x3c, 0xf3, 0xc, 0x31,
    0x80,

    /* U+04C9 "Ӊ" */
    0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfe, 0xc6, 0xc6,
    0xc6, 0xc6, 0xc7, 0x3, 0x3, 0x2,

    /* U+04CA "ӊ" */
    0xcd, 0x9b, 0x36, 0x6f, 0xd9, 0xb3, 0x67, 0x6,
    0xc, 0x10,

    /* U+04CB "Ӌ" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x6,
    0xc, 0x78, 0xc1, 0x83, 0x0,

    /* U+04CC "ӌ" */
    0xde, 0xf7, 0xb7, 0x8c, 0x67, 0x31, 0x8c,

    /* U+04CD "Ӎ" */
    0xe3, 0xb8, 0xee, 0x3b, 0x8e, 0xf7, 0xbd, 0x6d,
    0x5b, 0x56, 0xdd, 0xb2, 0x6c, 0x9c, 0x3, 0x0,
    0xc0, 0x20,

    /* U+04CE "ӎ" */
    0xe7, 0x73, 0xb9, 0xdc, 0xef, 0xb6, 0xdb, 0x6d,
    0xb7, 0x1, 0x80, 0xc0, 0x40,

    /* U+04CF "ӏ" */
    0xff, 0xff, 0xfc,

    /* U+04D0 "Ӑ" */
    0x64, 0x38, 0x18, 0x38, 0x38, 0x28, 0x6c, 0x6c,
    0x64, 0x7e, 0xc6, 0xc2, 0x83,

    /* U+04D1 "ӑ" */
    0x5b, 0x80, 0xed, 0x8d, 0xfb, 0xde, 0xde,

    /* U+04D2 "Ӓ" */
    0x6c, 0x0, 0x41, 0x82, 0x85, 0xa, 0x36, 0x44,
    0xfb, 0x1e, 0x18, 0x20,

    /* U+04D3 "ӓ" */
    0xd8, 0x0, 0xed, 0x8d, 0xfb, 0xde, 0xde,

    /* U+04D4 "Ӕ" */
    0x7, 0xf0, 0xf0, 0xf, 0x0, 0xb0, 0x1b, 0x1,
    0x3e, 0x33, 0x3, 0xf0, 0x63, 0x6, 0x30, 0x43,
    0xf0,

    /* U+04D5 "ӕ" */
    0x7f, 0x6c, 0xc6, 0x6f, 0xfd, 0x86, 0xc3, 0x70,
    0xff,

    /* U+04D6 "Ӗ" */
    0x49, 0x27, 0x3e, 0xc3, 0xc, 0x30, 0xfb, 0xc,
    0x30, 0xc3, 0xf0,

    /* U+04D7 "ӗ" */
    0x49, 0xe0, 0x1e, 0xcf, 0x3f, 0xf0, 0xc3, 0x27,
    0x80,

    /* U+04D8 "Ә" */
    0x78, 0x18, 0x18, 0x30, 0x7f, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+04D9 "ә" */
    0x70, 0x60, 0xc3, 0xff, 0x3c, 0x9e,

    /* U+04DA "Ӛ" */
    0x6c, 0x1, 0xe0, 0x60, 0x60, 0xc1, 0xff, 0xc7,
    0x8f, 0x1b, 0x63, 0x80,

    /* U+04DB "ӛ" */
    0xd8, 0x0, 0x1c, 0x18, 0x30, 0xff, 0xcf, 0x27,
    0x80,

    /* U+04DC "Ӝ" */
    0x1b, 0x0, 0x3, 0x19, 0xb3, 0x26, 0x6c, 0x4d,
    0xd, 0xa1, 0xfc, 0x36, 0x8c, 0xd9, 0x9b, 0x63,
    0x3c, 0x66,

    /* U+04DD "ӝ" */
    0x36, 0x0, 0x0, 0x1b, 0x3d, 0x92, 0xd9, 0xe8,
    0x7c, 0x7b, 0x2c, 0xb6, 0x60,

    /* U+04DE "Ӟ" */
    0x6c, 0x0, 0xf3, 0x3c, 0x60, 0xc3, 0x8e, 0xe,
    0xd, 0x1b, 0x33, 0xc0,

    /* U+04DF "ӟ" */
    0xd8, 0x0, 0xed, 0x8c, 0xc3, 0x1e, 0xdc,

    /* U+04E0 "Ӡ" */
    0x7c, 0x18, 0x20, 0xc1, 0x7, 0x81, 0x83, 0x46,
    0xcc, 0xf0,

    /* U+04E1 "ӡ" */
    0x7c, 0x18, 0x20, 0xc1, 0x7, 0x81, 0x83, 0x46,
    0xcc, 0xf0,

    /* U+04E2 "Ӣ" */
    0x78, 0x3, 0x1e, 0x7c, 0xf9, 0xf7, 0xeb, 0xf7,
    0xcf, 0x9f, 0x3c, 0x60,

    /* U+04E3 "ӣ" */
    0x78, 0x0, 0x33, 0xdf, 0x7d, 0xfb, 0xef, 0xbc,
    0xc0,

    /* U+04E4 "Ӥ" */
    0x6c, 0x3, 0x1e, 0x7c, 0xf9, 0xf7, 0xeb, 0xf7,
    0xcf, 0x9f, 0x3c, 0x60,

    /* U+04E5 "ӥ" */
    0xd8, 0x1, 0xbd, 0xef, 0xff, 0xde, 0xf6,

    /* U+04E6 "Ӧ" */
    0x6c, 0x0, 0xe3, 0x6c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1b, 0x63, 0x80,

    /* U+04E7 "ӧ" */
    0xd8, 0x0, 0x1e, 0xcf, 0x3c, 0xf3, 0xcf, 0x37,
    0x80,

    /* U+04E8 "Ө" */
    0x38, 0xdb, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+04E9 "ө" */
    0x79, 0x2c, 0xff, 0xcf, 0x34, 0x9e,

    /* U+04EA "Ӫ" */
    0x6c, 0x0, 0xe3, 0x6c, 0x78, 0xf1, 0xff, 0xc7,
    0x8f, 0x1b, 0x63, 0x80,

    /* U+04EB "ӫ" */
    0x6c, 0x0, 0x1, 0xc6, 0xcc, 0xbf, 0x62, 0x64,
    0xd8, 0xe0,

    /* U+04EC "Ӭ" */
    0x6c, 0x0, 0xe2, 0x6c, 0x78, 0xc1, 0x8f, 0x7,
    0x8f, 0x1a, 0x67, 0x80,

    /* U+04ED "ӭ" */
    0xd8, 0x0, 0x1c, 0xc8, 0x33, 0xc3, 0xcf, 0x67,
    0x0,

    /* U+04EE "Ӯ" */
    0x78, 0xc, 0xf3, 0x4d, 0x27, 0x9e, 0x30, 0xc3,
    0x8, 0x60,

    /* U+04EF "ӯ" */
    0x78, 0x0, 0x33, 0xc9, 0x67, 0x9e, 0x70, 0xc3,
    0x8, 0x23, 0x0,

    /* U+04F0 "Ӱ" */
    0x6c, 0x3, 0x1e, 0x24, 0xcd, 0x9a, 0x1c, 0x38,
    0x20, 0x41, 0x86, 0x0,

    /* U+04F1 "ӱ" */
    0x6c, 0x0, 0x1b, 0x6d, 0xb6, 0x8e, 0x38, 0xe1,
    0x4, 0x31, 0x80,

    /* U+04F2 "Ӳ" */
    0x3c, 0x50, 0x6, 0x2c, 0xc9, 0x9a, 0x34, 0x38,
    0x70, 0xc1, 0x83, 0xc, 0x0,

    /* U+04F3 "ӳ" */
    0x3c, 0xa0, 0x13, 0x4d, 0xa6, 0x8e, 0x38, 0xc3,
    0x4, 0x31, 0x80,

    /* U+04F4 "Ӵ" */
    0x6c, 0x3, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x7e,
    0xc, 0x18, 0x30, 0x60,

    /* U+04F5 "ӵ" */
    0xd8, 0x1, 0xbd, 0xef, 0x6f, 0x18, 0xc6,

    /* U+04F6 "Ӷ" */
    0xff, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xe,
    0x18, 0x61, 0x80,

    /* U+04F7 "ӷ" */
    0xfc, 0xcc, 0xcc, 0xce, 0x66, 0x60,

    /* U+04F8 "Ӹ" */
    0x36, 0x0, 0x30, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xf3, 0xcd, 0xe6, 0xf3, 0x79, 0xbf, 0x98,

    /* U+04F9 "ӹ" */
    0x66, 0x0, 0x0, 0xc3, 0xc3, 0xc3, 0xfb, 0xcf,
    0xcf, 0xcf, 0xfb,

    /* U+04FA "Ӻ" */
    0x7d, 0x86, 0x18, 0x63, 0xc6, 0x18, 0x61, 0x87,
    0xc, 0x31, 0x80,

    /* U+04FB "ӻ" */
    0x7b, 0x19, 0xe6, 0x31, 0x8e, 0x31, 0x98,

    /* U+04FC "Ӽ" */
    0xc6, 0x64, 0x6c, 0x2c, 0x38, 0x38, 0x38, 0x38,
    0x6c, 0x6c, 0xc7, 0x3, 0x3, 0x6,

    /* U+04FD "ӽ" */
    0x4c, 0xd0, 0xe1, 0x83, 0x7, 0x1a, 0x27, 0x6,
    0xc, 0x30,

    /* U+04FE "Ӿ" */
    0x66, 0x66, 0x24, 0x3c, 0x3c, 0x3c, 0x38, 0x3c,
    0x24, 0x66, 0x66,

    /* U+04FF "ӿ" */
    0xcd, 0xe7, 0x1e, 0x31, 0xe4, 0xb3
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 52, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 57, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 72, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 6, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 112, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 27, .adv_w = 142, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 126, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 38, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 50, .adv_w = 71, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 58, .adv_w = 72, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 66, .adv_w = 99, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 70, .adv_w = 109, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 76, .adv_w = 50, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 69, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 79, .adv_w = 62, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 78, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 88, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 112, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 57, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 52, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 181, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 186, .adv_w = 110, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 189, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 194, .adv_w = 98, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 172, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 219, .adv_w = 132, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 127, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 127, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 107, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 58, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 109, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 107, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 170, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 135, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 382, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 119, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 127, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 455, .adv_w = 120, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 118, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 58, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 481, .adv_w = 84, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 489, .adv_w = 58, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 495, .adv_w = 86, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 499, .adv_w = 90, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 500, .adv_w = 72, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 501, .adv_w = 106, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 72, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 551, .adv_w = 109, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 54, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 561, .adv_w = 53, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 567, .adv_w = 104, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 54, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 167, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 109, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 608, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 617, .adv_w = 71, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 102, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 68, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 109, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 97, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 665, .adv_w = 100, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 68, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 678, .adv_w = 56, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 680, .adv_w = 68, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 688, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 691, .adv_w = 111, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 111, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 109, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 733, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 119, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 752, .adv_w = 58, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 755, .adv_w = 58, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 109, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 205, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 791, .adv_w = 205, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 123, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 137, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 845, .adv_w = 123, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 858, .adv_w = 138, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 871, .adv_w = 132, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 109, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 909, .adv_w = 147, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 925, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 934, .adv_w = 188, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 951, .adv_w = 119, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 961, .adv_w = 137, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 971, .adv_w = 137, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 984, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 994, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1005, .adv_w = 170, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1018, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1028, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1038, .adv_w = 138, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1048, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1058, .adv_w = 127, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1068, .adv_w = 119, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1079, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1089, .adv_w = 157, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1101, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1111, .adv_w = 147, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1125, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1135, .adv_w = 185, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1149, .adv_w = 195, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1169, .adv_w = 148, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1180, .adv_w = 170, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1193, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1202, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1212, .adv_w = 178, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1226, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1235, .adv_w = 106, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1240, .adv_w = 111, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1249, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1255, .adv_w = 83, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1260, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1270, .adv_w = 106, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1276, .adv_w = 159, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1286, .adv_w = 101, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1292, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1298, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1307, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1313, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1319, .adv_w = 147, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1327, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1333, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1339, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1345, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1354, .adv_w = 103, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1360, .adv_w = 99, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1366, .adv_w = 97, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1375, .adv_w = 142, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1389, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1395, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1404, .adv_w = 109, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1409, .adv_w = 160, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1417, .adv_w = 171, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1431, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1439, .adv_w = 159, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1447, .adv_w = 109, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1453, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1459, .adv_w = 158, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1468, .adv_w = 109, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1474, .adv_w = 106, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1483, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1492, .adv_w = 109, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1503, .adv_w = 83, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1510, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1516, .adv_w = 102, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1521, .adv_w = 54, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1524, .adv_w = 56, .box_w = 5, .box_h = 11, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1531, .adv_w = 53, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1537, .adv_w = 165, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1547, .adv_w = 166, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1557, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1566, .adv_w = 110, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1575, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1584, .adv_w = 97, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1595, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1604, .adv_w = 177, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1618, .adv_w = 152, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1626, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1636, .adv_w = 109, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1647, .adv_w = 173, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1661, .adv_w = 146, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1669, .adv_w = 125, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1680, .adv_w = 108, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1687, .adv_w = 177, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1701, .adv_w = 152, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1710, .adv_w = 170, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1723, .adv_w = 145, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1731, .adv_w = 224, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1748, .adv_w = 195, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1759, .adv_w = 102, .box_w = 5, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1770, .adv_w = 98, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1780, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1791, .adv_w = 143, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1803, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1813, .adv_w = 111, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1819, .adv_w = 125, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1829, .adv_w = 101, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1835, .adv_w = 125, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1847, .adv_w = 101, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1856, .adv_w = 232, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1881, .adv_w = 209, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1898, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1910, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1918, .adv_w = 177, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1934, .adv_w = 152, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1944, .adv_w = 177, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1961, .adv_w = 152, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1972, .adv_w = 124, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1985, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1994, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2002, .adv_w = 0, .box_w = 5, .box_h = 3, .ofs_x = -5, .ofs_y = 8},
    {.bitmap_index = 2004, .adv_w = 0, .box_w = 4, .box_h = 2, .ofs_x = -5, .ofs_y = 9},
    {.bitmap_index = 2005, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = -3, .ofs_y = 10},
    {.bitmap_index = 2006, .adv_w = 0, .box_w = 1, .box_h = 2, .ofs_x = -3, .ofs_y = 10},
    {.bitmap_index = 2007, .adv_w = 0, .box_w = 13, .box_h = 13, .ofs_x = -10, .ofs_y = -3},
    {.bitmap_index = 2029, .adv_w = 0, .box_w = 13, .box_h = 13, .ofs_x = -10, .ofs_y = -3},
    {.bitmap_index = 2051, .adv_w = 152, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2068, .adv_w = 128, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2081, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2091, .adv_w = 109, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2102, .adv_w = 124, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2112, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2121, .adv_w = 108, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2131, .adv_w = 91, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2138, .adv_w = 109, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2148, .adv_w = 83, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2154, .adv_w = 123, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2164, .adv_w = 102, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2171, .adv_w = 201, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2192, .adv_w = 170, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2206, .adv_w = 119, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2217, .adv_w = 101, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2224, .adv_w = 144, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2238, .adv_w = 125, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2248, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2258, .adv_w = 117, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2264, .adv_w = 128, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2275, .adv_w = 107, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2285, .adv_w = 160, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2299, .adv_w = 139, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2308, .adv_w = 152, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2322, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2332, .adv_w = 187, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2346, .adv_w = 137, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2354, .adv_w = 200, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2372, .adv_w = 169, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2384, .adv_w = 151, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2395, .adv_w = 124, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2402, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2413, .adv_w = 103, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2422, .adv_w = 119, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2435, .adv_w = 99, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2444, .adv_w = 120, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2455, .adv_w = 101, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2464, .adv_w = 120, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2475, .adv_w = 101, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2484, .adv_w = 129, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2498, .adv_w = 107, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2507, .adv_w = 175, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2525, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2535, .adv_w = 149, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2549, .adv_w = 122, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2559, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2569, .adv_w = 109, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2574, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2584, .adv_w = 109, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2591, .adv_w = 149, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2604, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2611, .adv_w = 149, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2627, .adv_w = 117, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2637, .adv_w = 58, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2640, .adv_w = 188, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2660, .adv_w = 159, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2673, .adv_w = 126, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2685, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 2693, .adv_w = 152, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 2709, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2719, .adv_w = 138, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2732, .adv_w = 111, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2741, .adv_w = 153, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2755, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2765, .adv_w = 136, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2778, .adv_w = 109, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2785, .adv_w = 184, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2803, .adv_w = 160, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 2816, .adv_w = 58, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2819, .adv_w = 132, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2832, .adv_w = 106, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2839, .adv_w = 132, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2851, .adv_w = 106, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2858, .adv_w = 183, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2875, .adv_w = 163, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2884, .adv_w = 111, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2895, .adv_w = 106, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2904, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2914, .adv_w = 105, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2920, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2932, .adv_w = 105, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2941, .adv_w = 188, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2959, .adv_w = 159, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2972, .adv_w = 119, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2984, .adv_w = 101, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2991, .adv_w = 114, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3001, .adv_w = 114, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3011, .adv_w = 137, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3023, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3032, .adv_w = 137, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3044, .adv_w = 113, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3051, .adv_w = 135, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3063, .adv_w = 112, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3072, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3082, .adv_w = 111, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3088, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3100, .adv_w = 111, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3110, .adv_w = 129, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3122, .adv_w = 104, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3131, .adv_w = 123, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3141, .adv_w = 97, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3152, .adv_w = 123, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3164, .adv_w = 97, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3175, .adv_w = 123, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3188, .adv_w = 97, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3199, .adv_w = 136, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3211, .adv_w = 109, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3218, .adv_w = 109, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3229, .adv_w = 83, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3235, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3250, .adv_w = 159, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3261, .adv_w = 118, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 3272, .adv_w = 92, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3279, .adv_w = 134, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3293, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 3303, .adv_w = 124, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3314, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1024, .range_length = 135, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 1160, .range_length = 120, .glyph_id_start = 231,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 1, 0, 2, 0, 0, 0, 0,
    2, 3, 0, 0, 0, 4, 0, 4,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 7, 8, 9, 10, 11,
    0, 12, 12, 13, 14, 15, 12, 12,
    9, 16, 17, 18, 0, 19, 13, 20,
    21, 22, 23, 24, 25, 0, 0, 0,
    0, 0, 26, 27, 28, 0, 29, 30,
    0, 31, 0, 0, 32, 0, 31, 31,
    33, 27, 0, 34, 0, 35, 0, 36,
    37, 38, 36, 39, 40, 0, 0, 0,
    10, 10, 41, 42, 0, 0, 12, 12,
    13, 43, 44, 45, 14, 0, 46, 12,
    6, 47, 7, 42, 48, 10, 22, 49,
    12, 0, 14, 12, 12, 12, 9, 0,
    16, 8, 19, 46, 0, 22, 12, 12,
    12, 50, 51, 12, 52, 53, 54, 55,
    26, 56, 57, 58, 59, 29, 38, 28,
    0, 0, 60, 0, 0, 0, 33, 0,
    27, 28, 61, 36, 27, 38, 62, 0,
    0, 63, 64, 0, 65, 27, 66, 0,
    29, 29, 0, 58, 67, 0, 0, 0,
    0, 68, 69, 0, 0, 0, 36, 0,
    0, 0, 52, 65, 0, 0, 6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 33, 20, 36, 20, 36,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 70, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 27, 42,
    58, 42, 0, 0, 0, 22, 38, 0,
    0, 14, 0, 14, 0, 14, 0, 14,
    0, 12, 0, 0, 0, 0, 0, 0,
    0, 8, 28, 19, 0, 23, 36, 23,
    0, 22, 38, 0, 0, 0, 0, 0,
    0, 0, 31, 0, 0, 0, 0, 12,
    22, 38, 0, 0, 0, 0, 0, 0,
    12, 0, 0, 0, 12, 0, 12, 6,
    26, 6, 26, 0, 0, 10, 29, 9,
    29, 0, 29, 22, 38, 0, 0, 0,
    0, 0, 0, 0, 0, 9, 33, 0,
    0, 0, 33, 0, 27, 46, 36, 46,
    36, 46, 36, 0, 0, 42, 58, 0,
    0, 0, 58, 22, 38, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 1, 0, 2, 0, 0, 0, 3,
    2, 0, 4, 5, 0, 6, 7, 6,
    8, 0, 0, 0, 0, 0, 0, 0,
    9, 0, 0, 0, 0, 0, 0, 0,
    10, 0, 11, 0, 12, 0, 0, 0,
    12, 0, 0, 13, 0, 0, 0, 0,
    12, 0, 12, 0, 14, 15, 16, 17,
    18, 19, 20, 21, 0, 0, 22, 0,
    0, 0, 23, 0, 24, 24, 24, 25,
    24, 0, 0, 0, 0, 0, 26, 26,
    27, 26, 24, 28, 29, 30, 31, 32,
    33, 34, 32, 35, 0, 0, 36, 0,
    0, 0, 15, 0, 12, 0, 0, 0,
    13, 37, 0, 15, 0, 0, 38, 0,
    11, 0, 0, 0, 39, 0, 19, 0,
    0, 0, 0, 37, 0, 0, 12, 0,
    0, 12, 15, 38, 0, 19, 0, 40,
    0, 0, 0, 0, 41, 42, 0, 0,
    23, 43, 44, 26, 45, 24, 34, 46,
    26, 26, 26, 47, 26, 26, 27, 26,
    26, 24, 48, 32, 24, 34, 26, 49,
    26, 26, 50, 51, 52, 53, 26, 54,
    24, 24, 55, 26, 24, 29, 0, 0,
    0, 47, 26, 0, 26, 26, 32, 56,
    12, 57, 0, 0, 0, 0, 11, 0,
    0, 0, 58, 0, 0, 0, 0, 0,
    0, 0, 12, 27, 17, 32, 17, 32,
    12, 24, 12, 59, 12, 24, 12, 60,
    12, 24, 0, 0, 0, 0, 0, 0,
    0, 0, 26, 0, 0, 0, 61, 0,
    62, 0, 0, 0, 0, 19, 34, 0,
    0, 0, 26, 0, 56, 0, 0, 15,
    63, 0, 26, 0, 26, 0, 44, 12,
    24, 12, 24, 15, 0, 20, 32, 20,
    0, 19, 34, 15, 0, 40, 49, 64,
    65, 0, 0, 66, 67, 0, 0, 0,
    19, 34, 0, 0, 37, 47, 0, 26,
    0, 26, 40, 49, 0, 26, 0, 11,
    23, 11, 23, 0, 0, 0, 24, 68,
    24, 0, 24, 19, 34, 0, 0, 0,
    0, 0, 26, 0, 26, 12, 27, 12,
    24, 12, 27, 0, 0, 38, 32, 38,
    32, 38, 32, 40, 49, 0, 26, 0,
    26, 0, 26, 19, 34, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -8, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 3, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -25, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -26,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -13, 0, 0,
    0, 0, 0, 0, 0, -8, 0, -2,
    0, 0, -14, -2, -9, -6, 0, -14,
    0, 0, 0, 0, 0, -3, -1, 0,
    0, -2, -1, -5, -4, 0, 1, 0,
    2, 0, 2, -6, -6, 0, 0, 0,
    0, 0, 2, -6, -8, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -12, -18, -14, -12, -4, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    -3, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, -12, 0, 0,
    0, 0, -2, 0, 0, 0, -6, 0,
    -2, 0, -2, -5, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -4, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -2, 0, -2, 0,
    0, 0, -2, -3, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -28, 0, 0,
    0, 0, -20, 0, -26, 0, 2, 0,
    0, 0, 0, 0, 0, 0, -4, -2,
    0, 0, -2, -3, 0, 0, -2, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0,
    0, 0, -3, 0, 0, 0, 2, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 2, -3, 0, 0, 0, 0,
    2, 0, 2, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -3, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -13, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, -1, -3, 0,
    0, 0, -3, -4, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    0, 0, 0, -8, -10, 0, 0, -3,
    0, 0, 0, 0, -9, 0, -5, -6,
    0, 0, -10, 0, -6, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, -7, 0, 0, -26, -4,
    -21, -13, 0, -28, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, -14,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -40, 0, 0, 0, 0, -17, 0,
    -21, 0, 0, 0, 0, 0, -5, 0,
    -3, 0, -1, -1, 0, 0, -1, 0,
    0, 2, 0, 2, 0, 0, 0, 0,
    -11, 0, -18, 0, 0, 0, 0, 0,
    -13, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    -3, -2, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, -2, 0, 0, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, -26, -28, 0,
    0, 0, -11, -3, -25, -2, 2, 0,
    2, 2, 0, 2, 0, 0, -16, -10,
    0, -11, -17, -8, -10, 0, -9, -8,
    -6, -8, -7, 0, -6, 0, -9, 0,
    2, 0, -3, -10, -15, -14, -14, -9,
    -14, 0, -14, -10, -14, -15, 2, -14,
    -14, 0, -14, -4, -14, -11, -8, 0,
    -14, -11, -16, -3, 0, 0, 0, 2,
    0, -24, -11, 0, 0, 0, -8, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, -5, -5, 0, 0, -5, -3,
    0, 0, -3, -1, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, -15, -7, 0,
    0, 0, -5, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, 1, -4, -3,
    0, 0, -3, -2, 0, 0, -2, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -11, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 2, 0, 0, 0,
    0, 0, 0, -3, 0, 0, -2, 0,
    0, 0, -2, -3, 0, 0, 0, 0,
    2, 0, 2, 0, 0, 0, -3, 0,
    0, 0, 2, -4, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, -5, -5, -6, -3,
    0, 0, -3, 2, -5, -24, -11, 0,
    0, 0, -14, -3, -10, -2, 2, -10,
    2, 2, 1, 2, 0, 2, -7, -7,
    -2, -4, -7, -4, -6, -2, -4, -2,
    0, -3, -3, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -2, 0,
    0, 0, -2, -3, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, -1,
    0, 0, 0, 0, -2, 0, 0, -1,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, -2, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, -2, -7,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -12, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, -2, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, -2, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, -2, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 2, 0, 0,
    0, -16, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, -2, 2, 0, -3, 0,
    0, 5, 0, 2, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 0, 0,
    0, -15, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, -1, 1, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -14, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    -5, 0, -1, -5, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, -3,
    0, -2, 0, 0, 0, -2, 0, -3,
    -5, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, -5, 0, 0, 0, 0,
    -3, 0, 0, -3, 0, 0, -7, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -47, -49, 0, 0, 0, -22, -7,
    0, -5, 1, 0, 1, 1, 0, 1,
    0, 0, -20, -20, 0, -20, -19, -15,
    -20, 0, -17, -17, -12, -16, -13, 0,
    -12, 0, -18, 0, 1, 0, -7, -20,
    -28, -26, -26, -17, -27, 0, -26, -19,
    -26, -27, 3, -26, -26, 0, -26, -9,
    -26, -21, -16, 0, -27, -21, -30, -7,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -19, 0,
    -6, 0, -2, -9, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, -1, -2, 0, -3,
    -7, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, -3,
    0, -4, 0, 0, 0, -8, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -19, 0, -6, 0, -2, -9,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, -4, 0, 0,
    -1, -2, 0, -3, -7, 0, 0, 0,
    0, 0, 0, -6, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, -3, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, -4,
    0, 0, 0, -2, 0, 0, 0, 0,
    -2, 0, 0, -2, 0, 0, -4, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -44, -18, 0, 0, 0, -10, -3,
    0, 0, 2, 0, 0, 0, 0, 2,
    0, 0, -10, -7, 0, -10, -7, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, -9, 0, 2, 0, 0, -3,
    -9, -5, -8, 0, -3, 0, -4, -10,
    0, -5, 0, -3, 0, 0, -5, 0,
    -4, -3, 0, 0, -3, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    -3, 0, -2, -3, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, -2, 0, -3,
    -3, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, -3,
    0, 0, -3, 0, -3, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 2, -3, -3, 0, 0, 0,
    2, 0, 2, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, -3, 0, -3, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, -2, 0,
    -1, 0, -1, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -1, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0,
    0, 0, -3, 0, -3, 0, 2, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 1, 2, -3, -3, -1, 0, 0,
    2, 0, 2, -3, -3, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, -3, -3, -3, 0, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -19, 0,
    -6, 0, -1, -9, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -6, 0, 0, -1, -2, 0, -3,
    -7, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, -3,
    0, -4, 0, 0, 0, -7, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -19, 0, -6, 0, -1, -9,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    -1, -2, 0, -3, -7, 0, 0, 0,
    0, 0, 0, -5, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, -3, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, 0, -3, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -3, -3, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, -3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -3, -3, 0, 0, 0, 0, 0,
    -3, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, -2, 0, 0, 0, -2,
    0, 0, 0, 0, -1, 0, 0, -2,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, -1, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -12, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 2, 0, 0, -2,
    -2, -4, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -8,
    1, 0, -4, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 2, -2, -2, 0, 0, -1,
    0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, 0, 2, -3,
    -2, -4, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    -4, 0, 0, 0, 0, -15, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -11, -3, 0, 0, -1,
    0, 0, 0, 0, -5, 0, 0, -4,
    0, 0, -20, 0, -6, 0, 0, 0,
    0, -15, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -12,
    -4, 0, 0, -3, 0, 0, 0, 0,
    -5, 0, 0, -4, 0, 0, -22, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, -1, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -15, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -6, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -12, -6, 0, 0, -3,
    0, 0, 0, 0, -5, 0, 0, -4,
    0, 0, -22, 0, -6, 0, 0, 0,
    0, -15, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -13,
    -5, 0, 0, -2, 0, 0, 0, 0,
    -5, 0, 0, -4, 0, 0, -22, 0,
    -6, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 70,
    .right_class_cnt     = 68,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 3,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t custom_cyrillic_14 = {
#else
lv_font_t custom_cyrillic_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if CUSTOM_CYRILLIC_14*/
