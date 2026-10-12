#include "drivers/drivers.h"

#include <Arduino.h>
#include <lvgl.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "app/secure_mem.h"
#include "ui/screens/ui_settings_screen.h"

#include "ui/theme/ui_theme.h"
#include "ui/screens/ui_settings_screen.h"

static constexpr int CYD_TOUCH_CS = 33;
static constexpr int CYD_TOUCH_IRQ = 36;
static constexpr int CYD_TOUCH_CLK = 25;
static constexpr int CYD_TOUCH_MOSI = 32;
static constexpr int CYD_TOUCH_MISO = 39;

static TFT_eSPI tft;
static SPIClass touch_spi(VSPI);
static XPT2046_Touchscreen touch(CYD_TOUCH_CS, CYD_TOUCH_IRQ);
static lv_color_t draw_buf[UI_SCREEN_W * 40];

static uint32_t lvgl_tick(void) {
  return millis();
}

/*static void flush_display(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  const uint32_t w = area->x2 - area->x1 + 1;
  const uint32_t h = area->y2 - area->y1 + 1;

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(reinterpret_cast<uint16_t *>(px_map), w * h, true);
  tft.endWrite();
  lv_display_flush_ready(disp);
}*/

static void flush_display(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
  const uint32_t w = area->x2 - area->x1 + 1;
  const uint32_t h = area->y2 - area->y1 + 1;

  lv_draw_sw_rgb565_swap(px_map, w * h);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors(reinterpret_cast<uint16_t *>(px_map), w * h, false);
  tft.endWrite();
  lv_display_flush_ready(disp);
}

static void read_touch(lv_indev_t *indev, lv_indev_data_t *data) {
  (void)indev;
  if (ui_settings_screen_is_blanked() || ui_settings_screen_swallowing()) {
    if (touch.touched()) {
      if (ui_settings_screen_is_blanked()) ui_settings_screen_wake();
      data->state = LV_INDEV_STATE_RELEASED;
      return;
    }
    ui_settings_screen_swallow_done();
  }

  if (!touch.touched()) {
    data->state = LV_INDEV_STATE_RELEASED;
    return;
  }

  const TS_Point raw = touch.getPoint();
  const int x = map(raw.x, 200, 3800, 0, UI_SCREEN_W - 1);
  const int y = map(raw.y, 200, 3800, 0, UI_SCREEN_H - 1);
  data->point.x = constrain(x, 0, UI_SCREEN_W - 1);
  data->point.y = constrain(y, 0, UI_SCREEN_H - 1);
  data->state = LV_INDEV_STATE_PRESSED;
}

void drivers_init(void) {
  tft.begin();

  /* TEST RGB
  tft.fillScreen(TFT_RED);
  delay(2700);
  tft.fillScreen(TFT_GREEN);
  delay(2700);
  tft.fillScreen(TFT_BLUE);
  delay(2700);
 */

  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  touch_spi.begin(CYD_TOUCH_CLK, CYD_TOUCH_MISO, CYD_TOUCH_MOSI, CYD_TOUCH_CS);
  touch.begin(touch_spi);
  touch.setRotation(0);

  lv_init();
  lv_tick_set_cb(lvgl_tick);

  lv_display_t *disp = lv_display_create(UI_SCREEN_W, UI_SCREEN_H);
  lv_display_set_flush_cb(disp, flush_display);
  lv_display_set_buffers(disp, draw_buf, nullptr, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

  lv_indev_t *pointer = lv_indev_create();
  lv_indev_set_type(pointer, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(pointer, read_touch);


}

void drivers_wipe_framebuffer(void) {
  secure_wipe(draw_buf, sizeof(draw_buf));
}

void drivers_blank_panel(void) {
  tft.fillScreen(TFT_BLACK);
}
