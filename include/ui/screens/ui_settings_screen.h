#pragma once

void ui_settings_screen_init(void);
void ui_settings_screen_show(void);
void ui_settings_screen_poll(void);
bool ui_settings_screen_is_blanked(void);
void ui_settings_screen_wake(void);
void ui_settings_screen_hold_awake(bool hold);
bool ui_settings_screen_swallowing(void);
void ui_settings_screen_swallow_done(void);