#include <stdio.h>
#include <lvgl.h>
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_new_wallet.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/screens/ui_settings_advanced.h"
#include "ui/screens/ui_new_wallet_confirm.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static lv_obj_t *title_label;
static lv_obj_t *progress_bar;
static lv_obj_t *history;
static lv_obj_t *delete_button;

// Previous rolls, newest on the right, drawn as small die faces between the
// progress bar and the buttons. They are drawn straight from wallet_rolls()
// in the draw callback: no label text or other copy of the rolls is kept.
static constexpr int kHistoryDie = 20;
static constexpr int kHistoryGap = 3;
static constexpr int kHistorySlots = 8;
static constexpr int kHistoryWidth = kHistorySlots * kHistoryDie + (kHistorySlots - 1) * kHistoryGap;

static const bool kPips[6][9] = {
    {0, 0, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 1},
};

static void draw_history(lv_event_t *event) {
  if (lv_event_get_code(event) != LV_EVENT_DRAW_MAIN) return;
  lv_obj_t *obj = static_cast<lv_obj_t *>(lv_event_get_target(event));
  lv_layer_t *layer = lv_event_get_layer(event);
  lv_area_t coords;
  lv_obj_get_coords(obj, &coords);

  const int *rolls = wallet_rolls();
  const int count = wallet_roll_count();
  const int shown = count < kHistorySlots ? count : kHistorySlots;
  const int first = count - shown;  // oldest roll still on screen

  lv_draw_rect_dsc_t slot;
  lv_draw_rect_dsc_init(&slot);
  slot.radius = 3;

  lv_draw_rect_dsc_t pip;
  lv_draw_rect_dsc_init(&pip);
  pip.bg_opa = LV_OPA_COVER;
  pip.bg_color = lv_color_hex(UI_COLOR_BG);
  pip.radius = LV_RADIUS_CIRCLE;
  pip.border_width = 0;

  constexpr int pip_size = 4;
  constexpr int pip_gap = 2;
  constexpr int pip_origin = (kHistoryDie - (3 * pip_size + 2 * pip_gap)) / 2;

  for (int i = 0; i < kHistorySlots; i++) {
    lv_area_t box;
    box.x1 = coords.x1 + i * (kHistoryDie + kHistoryGap);
    box.y1 = coords.y1;
    box.x2 = box.x1 + kHistoryDie - 1;
    box.y2 = box.y1 + kHistoryDie - 1;

    if (i >= shown) {
      // Empty slot: outline only.
      slot.bg_opa = LV_OPA_TRANSP;
      slot.border_width = 1;
      slot.border_color = lv_color_hex(UI_COLOR_BUTTON);
      lv_draw_rect(layer, &slot, &box);
      continue;
    }

    const int face = rolls[first + i];
    const bool newest = first + i == count - 1;
    slot.bg_opa = LV_OPA_COVER;
    slot.bg_color = lv_color_hex(UI_COLOR_TEXT);
    slot.border_width = newest ? 2 : 0;
    slot.border_color = lv_color_hex(UI_COLOR_TITLE);
    lv_draw_rect(layer, &slot, &box);
    if (face < 1 || face > 6) continue;

    for (int p = 0; p < 9; p++) {
      if (!kPips[face - 1][p]) continue;
      lv_area_t dot;
      dot.x1 = box.x1 + pip_origin + (p % 3) * (pip_size + pip_gap);
      dot.y1 = box.y1 + pip_origin + (p / 3) * (pip_size + pip_gap);
      dot.x2 = dot.x1 + pip_size - 1;
      dot.y2 = dot.y1 + pip_size - 1;
      lv_draw_rect(layer, &pip, &dot);
    }
  }
}

static void refresh_progress(void) {
  char text[32];
  const int entered = wallet_roll_count();
  snprintf(text, sizeof(text), TR("Dice Roll %d of %d"), entered + 1, ui_settings_die_roll_count());
  lv_label_set_text(title_label, text);
  lv_bar_set_value(progress_bar, entered, LV_ANIM_OFF);
  if (history != nullptr) lv_obj_invalidate(history);
  if (delete_button != nullptr) {
    // Dimmed by hand: the default theme's disabled state paints a light grey.
    // With no rolls a click does nothing anyway (wallet_remove_last_roll fails).
    const bool any = entered > 0;
    lv_obj_set_style_bg_opa(delete_button, any ? LV_OPA_COVER : LV_OPA_40, 0);
    lv_obj_set_style_text_color(delete_button, lv_color_hex(any ? UI_COLOR_TEXT : UI_COLOR_MUTED), 0);
  }
}

static void add_pip(lv_obj_t *die, int col, int row) {
  constexpr int pip_size = 8;
  constexpr int gap = 8;
  constexpr int grid = 3 * pip_size + 2 * gap;
  constexpr int origin = (64 - grid) / 2;

  lv_obj_t *pip = lv_obj_create(die);
  lv_obj_set_size(pip, pip_size, pip_size);
  lv_obj_set_pos(pip, origin + col * (pip_size + gap), origin + row * (pip_size + gap));
  lv_obj_set_style_bg_color(pip, lv_color_hex(UI_COLOR_BG), 0);
  lv_obj_set_style_radius(pip, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_border_width(pip, 0, 0);
  lv_obj_set_style_pad_all(pip, 0, 0);
  lv_obj_set_scrollable(pip, false);
  lv_obj_set_clickable(pip, false);
}

static void draw_face(lv_obj_t *die, int face) {
  for (int i = 0; i < 9; i++) {
    if (kPips[face - 1][i]) {
      add_pip(die, i % 3, i / 3);
    }
  }
}

static void on_face_clicked(lv_event_t *event) {
  const int face = static_cast<int>(reinterpret_cast<intptr_t>(lv_event_get_user_data(event)));
  wallet_add_roll(face);
  if (wallet_roll_count() >= ui_settings_die_roll_count()) {
    ui_new_wallet_confirm_show();
    return;
  }
  refresh_progress();
}

static void on_history_deleted(lv_event_t *event) {
  (void)event;
  history = nullptr;
  delete_button = nullptr;
}

static void on_delete_clicked(lv_event_t *event) {
  (void)event;
  if (wallet_remove_last_roll()) refresh_progress();
}

static void on_cancel_clicked(lv_event_t *event) {
  (void)event;
  device_wipe_secrets();
  ui_main_menu_show();
  device_scrub_residue();
}

static lv_obj_t *make_die(lv_obj_t *parent, int face, int x, int y) {
  lv_obj_t *die = lv_button_create(parent);
  lv_obj_set_size(die, 64, 64);
  lv_obj_set_pos(die, x, y);
  lv_obj_set_style_bg_color(die, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_set_style_bg_color(die, lv_color_hex(UI_COLOR_TITLE), LV_STATE_PRESSED);
  lv_obj_set_style_radius(die, 8, 0);
  lv_obj_set_style_border_width(die, 0, 0);
  lv_obj_set_style_pad_all(die, 0, 0);
  lv_obj_set_scrollable(die, false);
  draw_face(die, face);
  lv_obj_add_event_cb(die, on_face_clicked, LV_EVENT_CLICKED, reinterpret_cast<void *>(static_cast<intptr_t>(face)));
  return die;
}

void ui_new_wallet_show(void) {
  wallet_clear_rolls();
  history = nullptr;
  delete_button = nullptr;

  lv_obj_t *screen = ui_make_screen();
  
  title_label = ui_make_title(screen, "");

  progress_bar = lv_bar_create(screen);
  lv_obj_set_size(progress_bar, 200, 10);
  lv_obj_align(progress_bar, LV_ALIGN_TOP_MID, 0, 52);
  lv_bar_set_range(progress_bar, 0, ui_settings_die_roll_count());
  lv_obj_set_style_bg_color(progress_bar, lv_color_hex(UI_COLOR_BUTTON), LV_PART_MAIN);
  lv_obj_set_style_bg_color(progress_bar, lv_color_hex(UI_COLOR_TITLE), LV_PART_INDICATOR);
  lv_obj_set_style_radius(progress_bar, 4, LV_PART_MAIN);
  lv_obj_set_style_radius(progress_bar, 4, LV_PART_INDICATOR);

  history = lv_obj_create(screen);
  lv_obj_remove_style_all(history);
  lv_obj_set_size(history, kHistoryWidth, kHistoryDie);
  lv_obj_align(history, LV_ALIGN_TOP_MID, 0, 70);
  lv_obj_set_scrollable(history, false);
  lv_obj_set_clickable(history, false);
  lv_obj_add_event_cb(history, draw_history, LV_EVENT_DRAW_MAIN, nullptr);
  lv_obj_add_event_cb(history, on_history_deleted, LV_EVENT_DELETE, nullptr);

  refresh_progress();

  const int origin_x = 20;
  const int origin_y = 98;
  const int gap = 12;
  for (int face = 1; face <= 6; face++) {
    const int col = (face - 1) % 3;
    const int row = (face - 1) / 3;
    make_die(screen, face, origin_x + col * (64 + gap), origin_y + row * (64 + gap));
  }

  lv_obj_t *cancel = lv_button_create(screen);
  lv_obj_set_size(cancel, UI_BUTTON_HALF_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(cancel, LV_ALIGN_BOTTOM_LEFT, 16, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(cancel, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(cancel, 8, 0);
  lv_obj_set_style_border_width(cancel, 0, 0);
  lv_obj_add_event_cb(cancel, on_cancel_clicked, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *label = lv_label_create(cancel);
  lv_label_set_text(label, TR("Cancel"));
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);

  // Removes the last roll, for a mistapped face. Dimmed with no rolls.
  delete_button = lv_button_create(screen);
  lv_obj_set_size(delete_button, UI_BUTTON_HALF_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(delete_button, LV_ALIGN_BOTTOM_RIGHT, -16, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(delete_button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(delete_button, 8, 0);
  lv_obj_set_style_border_width(delete_button, 0, 0);
  // Text colour is set on the button so the label follows refresh_progress().
  lv_obj_add_event_cb(delete_button, on_delete_clicked, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *delete_label = lv_label_create(delete_button);
  lv_label_set_text(delete_label, TR("Del"));
  lv_obj_set_style_text_font(delete_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_center(delete_label);

  refresh_progress();

  ui_screen_replace(screen);
}