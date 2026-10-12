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

static void refresh_progress(void) {
  char text[32];
  const int entered = wallet_roll_count();
  snprintf(text, sizeof(text), TR("Dice Roll %d of %d"), entered + 1, ui_settings_die_roll_count());
  lv_label_set_text(title_label, text);
  lv_bar_set_value(progress_bar, entered, LV_ANIM_OFF);
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
  const bool pips[6][9] = {
      {0, 0, 0, 0, 1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0, 0, 0, 0, 1},
      {1, 0, 0, 0, 1, 0, 0, 0, 1},
      {1, 0, 1, 0, 0, 0, 1, 0, 1},
      {1, 0, 1, 0, 1, 0, 1, 0, 1},
      {1, 0, 1, 1, 0, 1, 1, 0, 1},
  };
  for (int i = 0; i < 9; i++) {
    if (pips[face - 1][i]) {
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

  lv_obj_t *screen = ui_make_screen();
  
  title_label = ui_make_title(screen, "");

  progress_bar = lv_bar_create(screen);
  lv_obj_set_size(progress_bar, 200, 10);
  lv_obj_align(progress_bar, LV_ALIGN_TOP_MID, 0, 68);
  lv_bar_set_range(progress_bar, 0, ui_settings_die_roll_count());
  lv_obj_set_style_bg_color(progress_bar, lv_color_hex(UI_COLOR_BUTTON), LV_PART_MAIN);
  lv_obj_set_style_bg_color(progress_bar, lv_color_hex(UI_COLOR_TITLE), LV_PART_INDICATOR);
  lv_obj_set_style_radius(progress_bar, 4, LV_PART_MAIN);
  lv_obj_set_style_radius(progress_bar, 4, LV_PART_INDICATOR);
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
  lv_obj_set_size(cancel, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(cancel, LV_ALIGN_BOTTOM_MID, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(cancel, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(cancel, 8, 0);
  lv_obj_set_style_border_width(cancel, 0, 0);
  lv_obj_add_event_cb(cancel, on_cancel_clicked, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *label = lv_label_create(cancel);
  lv_label_set_text(label, TR("Cancel"));
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);

  ui_screen_replace(screen);
}