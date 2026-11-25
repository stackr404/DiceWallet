#include <stdio.h>
#include <lvgl.h>
#include "ui/screens/ui_helper.h"
#include "ui/screens/ui_wallet_view_public_keys.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/screens/ui_wallet_view_public_key.h"
#include "ui/screens/ui_wallet_passphrase.h"
#include "ui/theme/ui_theme.h"
#include "ui/ui_nav.h"
#include "app/secure_mem.h"
#include "app/wallet.h"
#include "coins/hd_coins.h"
#include "ui/text/ui_text.h"

static void show_coin(const char *title, const hd_watch_coin &coin) {
  wallet_generation_result w = wallet_generation();
  String pass(ui_wallet_passphrase());
  uint8_t fp[4] = {0, 0, 0, 0};
  String xpub = derive_account_xpub(w, pass, coin, 0, fp);
  secure_wipe(&w, sizeof(w));
  if (pass.length() > 0) secure_wipe(const_cast<char *>(pass.c_str()), pass.length());
  pass = "";

  // Key origin in descriptor form, e.g. [73c5da0a/84'/0'/0']. The master
  // fingerprint changes with every passphrase, so writing it down next to the
  // seed shows later whether the same passphrase was typed.
  char origin[48];
  const char *path = coin.note != nullptr ? coin.note : "";
  if (path[0] == 'm') path++;  // "m/84'/0'/0'" -> "/84'/0'/0'"
  if (xpub.length() > 0) {
    snprintf(origin, sizeof(origin), "[%02x%02x%02x%02x%s]", fp[0], fp[1], fp[2], fp[3], path);
  } else {
    snprintf(origin, sizeof(origin), "%s", coin.note != nullptr ? coin.note : "");
  }
  ui_wallet_view_public_key_show(title, xpub.c_str(), origin);
}

static void on_btc(lv_event_t *event)
{
  (void)event;
  show_coin(TR("Bitcoin (BTC)"), hd_coin_BTC);
}

static void on_eth(lv_event_t *event) {
  (void)event;
  show_coin(TR("Ethereum (ETH)"), hd_coin_ETH);
}

static void on_xrp(lv_event_t *event) {
  (void)event;
  show_coin(TR("XRP"), hd_coin_XRP);
}

static void on_cancel(lv_event_t *event) {
  (void)event;
  device_wipe_secrets();
  ui_main_menu_show();
  device_scrub_residue();
}

static lv_obj_t *add_coin_button(lv_obj_t *screen, const char *text, int y, lv_event_cb_t handler) {
  lv_obj_t *button = lv_button_create(screen);
  lv_obj_set_size(button, UI_BUTTON_FULL_WIDTH, UI_BUTTON_HEIGHT);
  lv_obj_align(button, LV_ALIGN_TOP_MID, 0, y);
  lv_obj_set_style_bg_color(button, lv_color_hex(UI_COLOR_BUTTON), 0);
  lv_obj_set_style_radius(button, 8, 0);
  lv_obj_set_style_border_width(button, 0, 0);
  lv_obj_add_event_cb(button, handler, LV_EVENT_CLICKED, nullptr);

  lv_obj_t *label = lv_label_create(button);
  lv_label_set_text(label, text);
  lv_obj_set_style_text_font(label, UI_FONT(UI_BUTTON_FONT_SIZE), 0);
  lv_obj_set_style_text_color(label, lv_color_hex(UI_COLOR_TEXT), 0);
  lv_obj_center(label);
  return button;
}

void ui_wallet_view_public_keys_show(void) {
  lv_obj_t *screen = ui_make_screen();

  ui_make_title(screen, TR("Public Keys"));

  add_coin_button(screen, TR("Bitcoin (BTC)"), 64, on_btc);
  add_coin_button(screen, TR("Ethereum (ETH)"), 120, on_eth);
  add_coin_button(screen, TR("XRP"), 176, on_xrp);
  add_coin_button(screen, TR("Main menu"), 248, on_cancel);

  ui_screen_replace(screen);
}