#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_wallet_display_seed.h"
#include "ui/screens/ui_new_wallet_seed_instructions.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "bip39/bip39_generator.h"
#include "ui/text/ui_text.h"

static const char *kLines[5] = {
  "Write down all 24 words.",
  "Keep the exact order shown.",
  "Never digitalize (no screenshots/typing).",
  "Store offline in a secure place.",
  "Never share with anyone."
};

static void on_show_seed(lv_event_t *event) {
    (void)event;

    const int *rolls = wallet_rolls();
    const int total = wallet_roll_count();

    wallet_generation_result wallet =
        generate_wallet_from_die_rolls(rolls, total, BIP39_EN);

    wallet_set_generation(wallet);
    wallet_clear_rolls();
    const bool ok = wallet.success;
    secure_wipe(&wallet, sizeof(wallet));

    if (!ok) {
        wallet_clear_generation();
        return;
    }

    ui_wallet_display_seed_show(false);
}

void ui_new_wallet_seed_instructions_show(void) {
  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Instructions"));

  lv_obj_t *list = lv_obj_create(screen);
  lv_obj_set_size(list, 228, 180);
  lv_obj_align(list, LV_ALIGN_TOP_MID, 0, 52);
  lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(list, 0, 0);
  lv_obj_set_style_pad_all(list, 0, 0);
  lv_obj_set_style_pad_row(list, 12, 0);
  lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_scrollable(list, false);

  for (int i = 0; i < 5; i++) {
    lv_obj_t *line = lv_label_create(list);
    lv_label_set_text(line, TR(kLines[i]));
    lv_obj_set_width(line, 220);
    lv_label_set_long_mode(line, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_font(line, UI_FONT(14), 0);
    lv_obj_set_style_text_color(line, lv_color_hex(UI_COLOR_TEXT), 0);
  }

  lv_obj_t *next = lv_button_create(screen);
  lv_obj_set_size(next, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(next, LV_ALIGN_BOTTOM_MID, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(next, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(next, 8, 0);
  lv_obj_set_style_border_width(next, 0, 0);
  lv_obj_add_event_cb(next, on_show_seed, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *label = lv_label_create(next);
  lv_label_set_text(label, TR("Show Seed Phrase"));
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);

  ui_screen_replace(screen);
}