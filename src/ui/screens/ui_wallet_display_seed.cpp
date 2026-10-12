#include "ui/screens/ui_wallet_display_seed.h"

#include <stdio.h>
#include <string.h>

#include <lvgl.h>

#include "app/secure_mem.h"
#include "app/wallet.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/screens/ui_new_wallet_verify_seed.h"
#include "ui/screens/ui_settings_advanced.h"
#include "ui/screens/ui_wallet_passphrase.h"
#include "ui/screens/ui_wallet_view_public_keys.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

enum SeedView {
  SEED_VIEW_WORDS = 0,
  SEED_VIEW_INDEX = 1,
  SEED_VIEW_HEX = 2,
  SEED_VIEW_BINARY = 3,
  SEED_VIEW_BINARY_VISUAL = 4,
  SEED_VIEW_COUNT = 5
};

static bool s_imported = false;
static lv_obj_t *s_labels[24];
static lv_obj_t *s_visual = nullptr;
static lv_obj_t *s_row_top = nullptr;
static lv_obj_t *s_row_bottom = nullptr;
static lv_obj_t *s_row_label = nullptr;
static lv_obj_t *s_row_up = nullptr;
static lv_obj_t *s_row_down = nullptr;
static const char *s_words[24];
static uint16_t s_indexes[24];
static int s_view = SEED_VIEW_WORDS;
static int s_highlight_row = 0;

static const int kCols = 11;
static const int kRows = 24;
static const int kTileW = 10;
static const int kTileH = 8;
static const int kVisualW = kCols * kTileW + (kCols + 1);
static const int kVisualH = kRows * kTileH + (kRows + 1);

static void format_line(char *out, size_t out_len, int n) {
  const int number = n + 1;
  const char *gap = number < 10 ? ". " : ".";
  const uint16_t index = s_indexes[n];
  switch (s_view) {
    case SEED_VIEW_INDEX:
      snprintf(out, out_len, "%d%s %04u", number, gap, (unsigned)index);
      break;
    case SEED_VIEW_HEX:
      snprintf(out, out_len, "%d%s %03X", number, gap, (unsigned)index);
      break;
    case SEED_VIEW_BINARY: {
      char bits[12];
      for (int b = 10; b >= 0; --b) bits[10 - b] = (index & (1u << b)) ? '1' : '0';
      bits[11] = '\0';
      snprintf(out, out_len, "%d%s%s", number, gap, bits);
      memset(bits, 0, sizeof(bits));
      break;
    }
    case SEED_VIEW_WORDS:
    default:
      snprintf(out, out_len, "%d%s %s", number, gap, s_words[n] != nullptr ? s_words[n] : "");
      break;
  }
}

static void on_visual_draw(lv_event_t *event) {
  if (lv_event_get_code(event) != LV_EVENT_DRAW_MAIN) return;
  lv_obj_t *obj = static_cast<lv_obj_t *>(lv_event_get_target(event));
  lv_layer_t *layer = lv_event_get_layer(event);
  lv_area_t coords;
  lv_obj_get_coords(obj, &coords);

  lv_draw_rect_dsc_t dsc;
  lv_draw_rect_dsc_init(&dsc);
  dsc.bg_opa = LV_OPA_COVER;
  dsc.border_width = 0;
  dsc.radius = 0;
  dsc.bg_color = lv_color_black();

  for (int row = 0; row < kRows; row++) {
    for (int col = 0; col < kCols; col++) {
      if ((s_indexes[row] & (1u << (10 - col))) == 0) continue;
      const int x = coords.x1 + 1 + col * (kTileW + 1);
      const int y = coords.y1 + 1 + row * (kTileH + 1);
      lv_area_t cell = {x, y, x + kTileW - 1, y + kTileH - 1};
      lv_draw_rect(layer, &dsc, &cell);
    }
  }

  dsc.bg_color = lv_color_hex(0xC8C8C8);
  for (int col = 0; col <= kCols; col++) {
    const int x = coords.x1 + col * (kTileW + 1);
    lv_area_t line = {x, coords.y1, x, coords.y2};
    lv_draw_rect(layer, &dsc, &line);
  }
  for (int row = 0; row <= kRows; row++) {
    const int y = coords.y1 + row * (kTileH + 1);
    lv_area_t line = {coords.x1, y, coords.x2, y};
    lv_draw_rect(layer, &dsc, &line);
  }

  if (s_highlight_row >= 0 && s_highlight_row < kRows) {
    const int y = coords.y1 + s_highlight_row * (kTileH + 1);
    lv_area_t box = {coords.x1, y, coords.x2, y + kTileH};
    dsc.bg_opa = LV_OPA_TRANSP;
    dsc.border_width = 1;
    dsc.border_color = lv_color_hex(0xFF0000);
    dsc.border_opa = LV_OPA_COVER;
    lv_draw_rect(layer, &dsc, &box);
  }
}

static void refresh_labels(void) {
  const bool visual = s_view == SEED_VIEW_BINARY_VISUAL;
  char line[32];
  for (int i = 0; i < 24; i++) {
    if (s_labels[i] == nullptr) continue;
    if (visual) {
      lv_obj_set_hidden(s_labels[i], true);
    } else {
      lv_obj_set_hidden(s_labels[i], false);
      format_line(line, sizeof(line), i);
      lv_label_set_text(s_labels[i], line);
    }
  }
  memset(line, 0, sizeof(line));
  if (s_row_top != nullptr) lv_obj_set_hidden(s_row_top, !visual);
  if (s_row_bottom != nullptr) lv_obj_set_hidden(s_row_bottom, !visual);
  if (s_row_label != nullptr) lv_obj_set_hidden(s_row_label, !visual);
  if (s_row_up != nullptr) lv_obj_set_hidden(s_row_up, !visual);
  if (s_row_down != nullptr) lv_obj_set_hidden(s_row_down, !visual);
  if (s_visual == nullptr) return;
  if (visual) {
    lv_obj_set_hidden(s_visual, false);
    lv_obj_move_foreground(s_visual);
    if (s_row_top != nullptr) lv_obj_move_foreground(s_row_top);
    if (s_row_bottom != nullptr) lv_obj_move_foreground(s_row_bottom);
    if (s_row_label != nullptr) lv_obj_move_foreground(s_row_label);
    if (s_row_up != nullptr) lv_obj_move_foreground(s_row_up);
    if (s_row_down != nullptr) lv_obj_move_foreground(s_row_down);
    lv_obj_invalidate(s_visual);
  } else {
    lv_obj_set_hidden(s_visual, true);
  }
}

static void show_highlight(void) {
  if (s_row_label != nullptr) {
    char text[4];
    snprintf(text, sizeof(text), (s_highlight_row + 1 < 10 ? " %d" : "%d"), s_highlight_row + 1);
    lv_label_set_text(s_row_label, text);
  }
  if (s_visual != nullptr) lv_obj_invalidate(s_visual);
}

static void on_row_up(lv_event_t *event) {
  (void)event;
  if (s_highlight_row > 0) s_highlight_row--;
  show_highlight();
}

static void on_row_down(lv_event_t *event) {
  (void)event;
  if (s_highlight_row + 1 < kRows) s_highlight_row++;
  show_highlight();
}

static void wipe_display_copies(void) {
  char blank[32];
  memset(blank, ' ', sizeof(blank) - 1);
  blank[sizeof(blank) - 1] = '\0';

  for (int i = 0; i < 24; i++) {
    if (s_labels[i] != nullptr) {
      char *text = lv_label_get_text(s_labels[i]);
      if (text != nullptr) secure_wipe(text, strlen(text));
      lv_label_set_text(s_labels[i], blank);
      s_labels[i] = nullptr;
    }
    s_words[i] = nullptr;
  }
  secure_wipe(s_indexes, sizeof(s_indexes));
  secure_wipe(blank, sizeof(blank));
  s_visual = nullptr;
  s_row_top = nullptr;
  s_row_bottom = nullptr;
  s_row_label = nullptr;
  s_row_up = nullptr;
  s_row_down = nullptr;
  s_highlight_row = 0;
  s_view = SEED_VIEW_WORDS;
}

static void on_words_tapped(lv_event_t *event) {
  if (lv_event_get_code(event) != LV_EVENT_CLICKED) return;
  if (!ui_settings_advanced_enabled()) return;
  s_view = (s_view + 1) % SEED_VIEW_COUNT;
  refresh_labels();
}

static void on_continue_clicked(lv_event_t *event) {
  (void)event;
  const char *words[24];
  uint16_t indexes[24];
  for (int i = 0; i < 24; i++) {
    words[i] = s_words[i];
    indexes[i] = s_indexes[i];
  }

  const bool imported = s_imported;
  s_imported = false;
  wipe_display_copies();

  if (imported) {
    if (ui_settings_advanced_enabled()) ui_wallet_passphrase_show();
    else ui_wallet_view_public_keys_show();
  } else {
    ui_new_wallet_verify_seed_show(words, indexes, BIP39_EN);
  }

  memset(indexes, 0, sizeof(indexes));
  secure_wipe(indexes, sizeof(indexes));
  for (int i = 0; i < 24; i++) words[i] = nullptr;
}

void ui_wallet_display_seed_show(bool imported) {
  s_imported = imported;
  s_view = SEED_VIEW_WORDS;
  wallet_generation_result w = wallet_generation();

  for (int i = 0; i < 24; i++) {
    s_words[i] = w.mnemonic_24_words != nullptr ? w.mnemonic_24_words[i] : nullptr;
    s_indexes[i] = w.word_indexes != nullptr ? w.word_indexes[i] : 0;
    s_labels[i] = nullptr;
  }
  s_visual = nullptr;
  s_row_top = nullptr;
  s_row_bottom = nullptr;
  s_row_label = nullptr;
  s_row_up = nullptr;
  s_row_down = nullptr;
  s_highlight_row = 0;

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Secret Recovery Phrase"), false);

  lv_obj_t *area = lv_obj_create(screen);
  lv_obj_set_pos(area, 0, 33);
  lv_obj_set_size(area, 240, 241);
  lv_obj_set_style_bg_opa(area, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(area, 0, 0);
  lv_obj_set_style_pad_all(area, 0, 0);
  lv_obj_set_scrollable(area, false);
  lv_obj_set_clickable(area, true);
  lv_obj_add_event_cb(area, on_words_tapped, LV_EVENT_CLICKED, nullptr);

  const int visual_x = 60;
  const int visual_y = 10;
  s_visual = lv_obj_create(area);
  lv_obj_set_size(s_visual, kVisualW, kVisualH);
  lv_obj_set_pos(s_visual, visual_x, visual_y);
  lv_obj_set_style_bg_color(s_visual, lv_color_white(), 0);
  lv_obj_set_style_bg_opa(s_visual, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(s_visual, 0, 0);
  lv_obj_set_style_pad_all(s_visual, 0, 0);
  lv_obj_set_style_radius(s_visual, 0, 0);
  lv_obj_set_scrollable(s_visual, false);
  lv_obj_set_clickable(s_visual, false);
  lv_obj_add_event_cb(s_visual, on_visual_draw, LV_EVENT_DRAW_MAIN, nullptr);
  lv_obj_set_hidden(s_visual, true);

  s_row_top = lv_label_create(area);
  lv_label_set_text(s_row_top, "1");
  lv_obj_set_style_text_font(s_row_top, &lv_font_unscii_8, 0);
  lv_obj_set_style_text_color(s_row_top, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_set_pos(s_row_top, visual_x - 14, visual_y + 1);
  lv_obj_set_hidden(s_row_top, true);

  s_row_bottom = lv_label_create(area);
  lv_label_set_text(s_row_bottom, "24");
  lv_obj_set_style_text_font(s_row_bottom, &lv_font_unscii_8, 0);
  lv_obj_set_style_text_color(s_row_bottom, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_set_pos(s_row_bottom, visual_x - 20, visual_y + 1 + 23 * (kTileH + 1));
  lv_obj_set_hidden(s_row_bottom, true);

  const int side_x = visual_x + kVisualW + 12;
  const int side_y = visual_y + 36;
  s_row_up = lv_button_create(area);
  lv_obj_set_size(s_row_up, 22, 22);
  lv_obj_set_pos(s_row_up, side_x, side_y + 36);
  lv_obj_set_style_bg_color(s_row_up, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(s_row_up, 4, 0);
  lv_obj_set_style_border_width(s_row_up, 0, 0);
  lv_obj_set_style_pad_all(s_row_up, 0, 0);
  lv_obj_add_event_cb(s_row_up, on_row_up, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *up_label = lv_label_create(s_row_up);
  lv_label_set_text(up_label, "-");
  lv_obj_set_style_text_font(up_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(up_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(up_label);
  lv_obj_set_hidden(s_row_up, true);

  s_row_label = lv_label_create(area);
  lv_label_set_text(s_row_label, " 1");
  lv_obj_set_style_text_font(s_row_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(s_row_label, lv_color_hex(UI_COLOR_TITLE), 0);
  lv_obj_set_pos(s_row_label, side_x + 4, side_y + 64);
  lv_obj_set_hidden(s_row_label, true);

  s_row_down = lv_button_create(area);
  lv_obj_set_size(s_row_down, 22, 22);
  lv_obj_set_pos(s_row_down, side_x, side_y + 86);
  lv_obj_set_style_bg_color(s_row_down, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(s_row_down, 4, 0);
  lv_obj_set_style_border_width(s_row_down, 0, 0);
  lv_obj_set_style_pad_all(s_row_down, 0, 0);
  lv_obj_add_event_cb(s_row_down, on_row_down, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *down_label = lv_label_create(s_row_down);
  lv_label_set_text(down_label, "+");
  lv_obj_set_style_text_font(down_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(down_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(down_label);
  lv_obj_set_hidden(s_row_down, true);

  for (int i = 0; i < 12; i++) {
    const int y = 8 + i * 18;
    s_labels[i] = lv_label_create(area);
    lv_obj_set_style_text_font(s_labels[i], &lv_font_unscii_8, 0);
    lv_obj_set_style_text_color(s_labels[i], lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_set_pos(s_labels[i], 6, y);

    s_labels[i + 12] = lv_label_create(area);
    lv_obj_set_style_text_font(s_labels[i + 12], &lv_font_unscii_8, 0);
    lv_obj_set_style_text_color(s_labels[i + 12], lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_set_pos(s_labels[i + 12], 124, y);
  }
  refresh_labels();

  lv_obj_t *next = lv_button_create(screen);
  lv_obj_set_size(next, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(next, LV_ALIGN_BOTTOM_MID, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(next, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(next, 8, 0);
  lv_obj_set_style_border_width(next, 0, 0);
  lv_obj_add_event_cb(next, on_continue_clicked, LV_EVENT_CLICKED, nullptr);
  lv_obj_move_foreground(next);

  lv_obj_t *label = lv_label_create(next);
  lv_label_set_text(label, TR("Continue"));
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);

  ui_screen_replace(screen);
}
void ui_wallet_display_seed_wipe(void) {
  wipe_display_copies();
  s_imported = false;
}