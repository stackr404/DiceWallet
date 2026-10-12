#include <lvgl.h>
#include "dice/die_fairness.h"
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/screens/ui_new_wallet_seed_instructions.h"
#include "ui/screens/ui_new_wallet_confirm.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

static void on_start_again(lv_event_t *event)
{
    (void)event;
    ui_main_menu_show();
}

static void on_proceed(lv_event_t *event)
{
    (void)event;
    // ui_main_menu_show();
    ui_new_wallet_seed_instructions_show();
}

static void add_result_row(lv_obj_t *screen, const char *name, bool passed, int y)
{
    const uint32_t color = passed ? UI_COLOR_SUCCESS : UI_COLOR_ERROR;

    lv_obj_t *test = lv_label_create(screen);
    lv_label_set_text(test, name);
    lv_obj_set_style_text_font(test, UI_FONT(14), 0);
    lv_obj_set_style_text_color(test, lv_color_hex(color), 0);
    lv_obj_set_pos(test, 16, y);

    lv_obj_t *status = lv_label_create(screen);
    lv_label_set_text(status, passed ? TR("Pass") : TR("Fail"));
    lv_obj_set_style_text_font(status, UI_FONT(14), 0);
    lv_obj_set_style_text_color(status, lv_color_hex(color), 0);
    lv_obj_set_pos(status, 176, y);
}

void ui_new_wallet_warning_show(const fairness_report *report)
{
    const bool passed[7] = {
        report != nullptr && chi_passed(report->chi),
        report != nullptr && runs_passed(report->runs),
        report != nullptr && serial_passed(report->serial),
        report != nullptr && gap_passed(report->gap),
        report != nullptr && longest_passed(report->longest),
        report != nullptr && poker_passed(report->poker),
        report != nullptr && autocorr_passed(report->autocorr)};
    static const char *names[7] = {
        TR("Chi-square"),
        TR("Runs"),
        TR("Serial"),
        TR("Gap"),
        TR("Longest run"),
        TR("Poker"),
        TR("Autocorrelation")};

    lv_obj_t *screen = ui_make_screen();

    ui_make_title(screen, TR("Dice Fairness Tests"));

    for (int i = 0; i < 7; i++)
    {
        add_result_row(screen, names[i], passed[i], 48 + i * 24);
    }

    lv_obj_t *again = lv_button_create(screen);
    lv_obj_set_size(again, UI_BUTTON_HALF_WIDTH, UI_BUTTON_HEIGHT);
    lv_obj_align(again, LV_ALIGN_BOTTOM_LEFT, 16, -12);
    lv_obj_set_style_bg_color(again, lv_color_hex(UI_COLOR_BUTTON), 0);
    lv_obj_set_style_radius(again, 8, 0);
    lv_obj_set_style_border_width(again, 0, 0);
    lv_obj_add_event_cb(again, on_start_again, LV_EVENT_CLICKED, nullptr);
    lv_obj_t *again_label = lv_label_create(again);
    lv_label_set_text(again_label, TR("Start Again"));
    lv_obj_set_style_text_font(again_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
    lv_obj_set_style_text_color(again_label, lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_center(again_label);

    lv_obj_t *proceed = lv_button_create(screen);
    lv_obj_set_size(proceed, UI_BUTTON_HALF_WIDTH, UI_BUTTON_HEIGHT);
    lv_obj_align(proceed, LV_ALIGN_BOTTOM_RIGHT, -16, -12);
    lv_obj_set_style_bg_color(proceed, lv_color_hex(UI_COLOR_BUTTON), 0);
    lv_obj_set_style_radius(proceed, 8, 0);
    lv_obj_set_style_border_width(proceed, 0, 0);
    lv_obj_add_event_cb(proceed, on_proceed, LV_EVENT_CLICKED, nullptr);
    lv_obj_t *proceed_label = lv_label_create(proceed);
    lv_label_set_text(proceed_label, TR("Proceed"));
    lv_obj_set_style_text_font(proceed_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
    lv_obj_set_style_text_color(proceed_label, lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_center(proceed_label);

    ui_screen_replace(screen);
}