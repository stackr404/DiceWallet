#include <Arduino.h>
#include <Preferences.h>
#include <esp_efuse.h>
#include <esp_efuse_table.h>
#include <esp_err.h>
#include <esp_secure_boot.h>
#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_settings_predelivery.h"
#include "ui/screens/ui_settings_menu.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "ui/text/ui_text.h"

// Legacy key. Secured state is the eFuse bits themselves; this is only erased.
static const char *kNamespace = "dicewallet";
static const char *kKeyDone = "predeliver";

struct FuseItem {
  const char *name;
  const esp_efuse_desc_t **field;
};

static const FuseItem kFuses[] = {
  {"DISABLE_BT", ESP_EFUSE_DISABLE_BT},
  {"JTAG_DISABLE", ESP_EFUSE_JTAG_DISABLE},
  {"UART_DOWNLOAD_DIS", ESP_EFUSE_UART_DOWNLOAD_DIS},
  {"CONSOLE_DEBUG_DISABLE", ESP_EFUSE_CONSOLE_DEBUG_DISABLE},
};

static const char *s_fail_name = nullptr;
// Burning is two taps: "Secure Device" shows what will happen, "Burn eFuses" does it.
static bool s_confirming = false;
static bool s_blocked_no_secure_boot = false;

static bool fuse_is_burned(const FuseItem &fuse) {
  return esp_efuse_read_field_bit(fuse.field);
}

static bool fuses_burned(void) {
  for (unsigned i = 0; i < sizeof(kFuses) / sizeof(kFuses[0]); i++) {
    if (!fuse_is_burned(kFuses[i])) return false;
  }
  return true;
}

// Drop a flag that used to be written even when esp_efuse_write_field_bit failed.
static void erase_stale_nvs_flag(void) {
  static bool erased = false;
  if (erased) return;
  erased = true;
  Preferences prefs;
  if (!prefs.begin(kNamespace, false)) return;
  prefs.remove(kKeyDone);
  prefs.end();
}

// Secured means the lock fuses are burned AND the bootloader has enabled
// Secure Boot v2. Fuses alone do not stop someone rewriting the SPI flash.
bool ui_settings_predelivery_done(void) {
  return fuses_burned() && esp_secure_boot_enabled();
}

static void on_back(lv_event_t *event) {
  (void)event;
  if (s_confirming) {
    s_confirming = false;
    ui_settings_predelivery_show();
    return;
  }
  s_blocked_no_secure_boot = false;
  s_fail_name = nullptr;
  ui_settings_menu_show();
}

// First tap. Refuse while Secure Boot is off: UART_DOWNLOAD_DIS would then
// block every future update over USB while the flash chip itself can still be
// rewritten with a clip, so the device would look locked without being safe.
static void on_secure(lv_event_t *event) {
  (void)event;
  s_fail_name = nullptr;
  s_blocked_no_secure_boot = !esp_secure_boot_enabled();
  s_confirming = !s_blocked_no_secure_boot;
  ui_settings_predelivery_show();
}

// Second tap: burn. eFuses are permanent.
static void on_confirm(lv_event_t *event) {
  (void)event;
  s_confirming = false;
  s_fail_name = nullptr;
  if (!esp_secure_boot_enabled()) {
    s_blocked_no_secure_boot = true;
    ui_settings_predelivery_show();
    return;
  }
  for (unsigned i = 0; i < sizeof(kFuses) / sizeof(kFuses[0]); i++) {
    if (fuse_is_burned(kFuses[i])) continue;
    const esp_err_t err = esp_efuse_write_field_bit(kFuses[i].field);
    if (err != ESP_OK || !fuse_is_burned(kFuses[i])) {
      s_fail_name = kFuses[i].name;
      break;
    }
  }
  ui_settings_predelivery_show();
}

void ui_settings_predelivery_show(void) {
  erase_stale_nvs_flag();
  const bool fuses_done = fuses_burned();
  const bool secure_boot = esp_secure_boot_enabled();
  const bool done = fuses_done && secure_boot;

  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Pre-delivery"));

  lv_obj_t *list = lv_obj_create(screen);
  lv_obj_set_size(list, 220, 100);
  lv_obj_align(list, LV_ALIGN_TOP_MID, 0, 42);
  lv_obj_set_style_bg_opa(list, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(list, 0, 0);
  lv_obj_set_style_pad_all(list, 0, 0);
  lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);

  bool any = false;
  for (unsigned i = 0; i < sizeof(kFuses) / sizeof(kFuses[0]); i++) {
    if (fuse_is_burned(kFuses[i])) continue;
    any = true;
    lv_obj_t *row = lv_label_create(list);
    lv_label_set_text(row, kFuses[i].name);
    lv_obj_set_style_text_font(row, UI_FONT(14), 0);
    lv_obj_set_style_text_color(row, lv_color_hex(UI_COLOR_TEXT), 0);
  }
  if (!secure_boot) {
    lv_obj_t *row = lv_label_create(list);
    lv_label_set_text(row, TR("Secure Boot Off"));
    lv_obj_set_style_text_font(row, UI_FONT(14), 0);
    lv_obj_set_style_text_color(row, lv_color_hex(UI_COLOR_TITLE), 0);
    any = true;
  }
  if (!any) {
    lv_obj_t *row = lv_label_create(list);
    lv_label_set_text(row, TR("Secured"));
    lv_obj_set_style_text_font(row, UI_FONT(14), 0);
    lv_obj_set_style_text_color(row, lv_color_hex(UI_COLOR_MUTED), 0);
  }

  lv_obj_t *status = lv_label_create(screen);
  lv_obj_set_width(status, 220);
  lv_label_set_long_mode(status, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_align(status, LV_TEXT_ALIGN_CENTER, 0);
  lv_obj_set_style_text_font(status, UI_FONT(14), 0);
  lv_obj_align(status, LV_ALIGN_TOP_MID, 0, 146);
  if (s_confirming) {
    lv_label_set_text(status, TR("Permanent. USB flashing and debug will be disabled for good. No firmware updates after this."));
    lv_obj_set_style_text_color(status, lv_color_hex(UI_COLOR_TITLE), 0);
  } else if (s_blocked_no_secure_boot || (!secure_boot && fuses_done)) {
    lv_label_set_text(status, TR("Secure Boot is off. Flash the esp32dev_secure build first."));
    lv_obj_set_style_text_color(status, lv_color_hex(UI_COLOR_TITLE), 0);
  } else if (s_fail_name != nullptr) {
    char line[64];
    snprintf(line, sizeof(line), "%s: %s", TR("Fuse write failed"), s_fail_name);
    lv_label_set_text(status, line);
    lv_obj_set_style_text_color(status, lv_color_hex(UI_COLOR_TITLE), 0);
  } else if (done) {
    lv_label_set_text(status, TR("Secured"));
    lv_obj_set_style_text_color(status, lv_color_hex(UI_COLOR_MUTED), 0);
  } else {
    lv_label_set_text(status, "");
  }

  if (!fuses_done) {
    lv_obj_t *secure = lv_button_create(screen);
    lv_obj_set_size(secure, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
    lv_obj_align(secure, LV_ALIGN_BOTTOM_MID, 0, -68);
    lv_obj_set_style_bg_color(secure, lv_color_hex(UI_COLOR_BUTTON), 0);
    lv_obj_set_style_radius(secure, 8, 0);
    lv_obj_set_style_border_width(secure, 0, 0);
    lv_obj_add_event_cb(secure, s_confirming ? on_confirm : on_secure, LV_EVENT_CLICKED, nullptr);
    lv_obj_t *secure_label = lv_label_create(secure);
    lv_label_set_text(secure_label, s_confirming ? TR("Burn eFuses") : TR("Secure Device"));
    lv_obj_set_style_text_font(secure_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
    lv_obj_set_style_text_color(secure_label, lv_color_hex(UI_COLOR_TEXT), 0);
    lv_obj_center(secure_label);
  }

  lv_obj_t *back = lv_button_create(screen);
  lv_obj_set_size(back, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(back, UI_BUTTON_BOTTOM_ALIGN, 0, UI_BUTTON_BOTTOM_Y_OFFSET);
  lv_obj_set_style_bg_color(back, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(back, 8, 0);
  lv_obj_set_style_border_width(back, 0, 0);
  lv_obj_add_event_cb(back, on_back, LV_EVENT_CLICKED, nullptr);
  lv_obj_t *back_label = lv_label_create(back);
  lv_label_set_text(back_label, s_confirming ? TR("Cancel") : TR("Settings"));
  lv_obj_set_style_text_font(back_label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(back_label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(back_label);

  ui_screen_replace(screen);
}