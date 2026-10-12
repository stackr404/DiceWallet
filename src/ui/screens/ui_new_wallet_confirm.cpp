#include <stdio.h>
#include <lvgl.h>
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "dice/die_rolls.h"
#include "dice/die_fairness.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/screens/ui_new_wallet_warning.h"
#include "ui/screens/ui_new_wallet_seed_instructions.h"
#include "ui/screens/ui_new_wallet_confirm.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

enum wallet_status {
  WALLET_STATUS_SUCCESS,
  WALLET_STATUS_WARNING,
  WALLET_STATUS_ERROR
};

static wallet_status s_status = WALLET_STATUS_SUCCESS;
static fairness_report s_report = {};

static wallet_status status_from_verdict(fairness_verdict verdict) {
  if (verdict == fairness_verdict::error) return WALLET_STATUS_ERROR;
  if (verdict == fairness_verdict::warning) return WALLET_STATUS_WARNING;
  return WALLET_STATUS_SUCCESS;
}

static void on_continue_clicked(lv_event_t *event) {
  (void)event;
  if (s_status == WALLET_STATUS_ERROR) {
    // Unfair die: do not derive a wallet. Rolls are not a usable entropy source.
    device_wipe_secrets();
    ui_main_menu_show();
    device_scrub_residue();
    return;
  }
  ui_new_wallet_seed_instructions_show();
}

static void add_status_bar(lv_obj_t *screen, wallet_status status) {
  uint32_t color = UI_COLOR_SUCCESS;
  const char *text = TR("Success");
  if (status == WALLET_STATUS_WARNING) {
    color = UI_COLOR_WARNING;
    text = TR("Warning");
  } else if (status == WALLET_STATUS_ERROR) {
    color = UI_COLOR_ERROR;
    text = TR("Error");
  }
  lv_obj_t *bar = lv_obj_create(screen);
  lv_obj_set_size(bar, 200, 36);
  lv_obj_align(bar, LV_ALIGN_TOP_MID, 0, 52);
  lv_obj_set_style_bg_color(bar, lv_color_hex(color), 0);
  lv_obj_set_style_radius(bar, 6, 0);
  lv_obj_set_style_border_width(bar, 0, 0);
  lv_obj_set_scrollable(bar, false);

  lv_obj_t *label = lv_label_create(bar);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);
}

static void add_frequency_chart(lv_obj_t *screen) {
  int counts[6] = {0, 0, 0, 0, 0, 0};
  const int *rolls = wallet_rolls();
  const int total = wallet_roll_count();
  for (int i = 0; i < total && i < k_max_die_rolls; i++) {
    const int face = rolls[i];
    if (face >= 1 && face <= 6) {
      counts[face - 1]++;
    }
  }

  int max_count = 1;
  for (int i = 0; i < 6; i++) {
    if (counts[i] > max_count) {
      max_count = counts[i];
    }
  }

  for (int face = 1; face <= 6; face++) {
    const int y = 104 + (face - 1) * 26;

    char name[4];
    snprintf(name, sizeof(name), "%d", face);
    lv_obj_t *label = lv_label_create(screen);
    lv_label_set_text(label, name);
    lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
    lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_set_pos(label, 12, y + 2);

    lv_obj_t *bar = lv_bar_create(screen);
    lv_obj_set_size(bar, 176, 14);
    lv_obj_set_pos(bar, 28, y);
    lv_bar_set_range(bar, 0, max_count);
    lv_bar_set_value(bar, counts[face - 1], LV_ANIM_OFF);
    lv_obj_set_style_bg_color(bar, lv_color_hex(UI_COLOR_BUTTON), LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar, lv_color_hex(UI_COLOR_FACES[face - 1]), LV_PART_INDICATOR);
    lv_obj_set_style_radius(bar, 3, LV_PART_MAIN);
    lv_obj_set_style_radius(bar, 3, LV_PART_INDICATOR);

    char value[8];
    snprintf(value, sizeof(value), "%d", counts[face - 1]);
    lv_obj_t *count = lv_label_create(screen);
    lv_label_set_text(count, value);
    lv_obj_set_style_text_font(count, UI_FONT(14), 0);
    lv_obj_set_style_text_color(count, lv_color_hex(UI_COLOR_MUTED), 0);
    lv_obj_set_pos(count, 208, y);
  }
}

void ui_new_wallet_confirm_show(void) {
  const int *rolls = wallet_rolls();
  const int total = wallet_roll_count();
  s_report = run_die_fairness_tests(rolls, total);
  s_status = status_from_verdict(run_fairness_verdict(s_report));

  if (s_status == WALLET_STATUS_WARNING) {
    ui_new_wallet_warning_show(&s_report);
    return;
  }

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Die Rolls"));

  add_status_bar(screen, s_status);
  add_frequency_chart(screen);

  lv_obj_t *next = lv_button_create(screen);
  lv_obj_set_size(next, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(next, LV_ALIGN_BOTTOM_MID, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(next, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(next, 8, 0);
  lv_obj_set_style_border_width(next, 0, 0);
  lv_obj_add_event_cb(next, on_continue_clicked, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *label = lv_label_create(next);
  lv_label_set_text(label, s_status == WALLET_STATUS_ERROR ? TR("Main Menu") : TR("Continue"));
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);

  ui_screen_replace(screen);
}
