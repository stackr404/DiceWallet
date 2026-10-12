#include <Arduino.h>
#include <lvgl.h>
#include <Preferences.h>
#include "drivers/drivers.h"
#include "ui/screens/ui_settings_screen.h"
#include "ui/text/ui_text.h"
#include "ui/screens/ui_settings_screen.h"
#include "ui/screens/ui_settings_advanced.h"
#include "ui/screens/ui_main_menu.h"
#include "ui/screens/ui_settings_language.h"
#include "ui/screens/ui_splash.h"

// PlatformIO defines UNIT_TEST while building pio test, which supplies its own setup/loop.
#ifndef UNIT_TEST
void setup()
{
  // Block serial 
  Serial.end();
  drivers_init();
  ui_settings_screen_init();
  ui_settings_advanced_init();
  ui_settings_language_init();
  ui_splash_show();
}

void loop()
{
  lv_timer_handler();
  // Check when to turn off screen
  ui_settings_screen_poll();
  // Check when to wipe device
  ui_settings_advanced_poll();
  delay(5);
}
#endif
