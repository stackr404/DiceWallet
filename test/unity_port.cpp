#include <Arduino.h>

// weak: PlatformIO compiles every cpp under test/, so a leftover copy must not fail the link.
extern "C" __attribute__((weak)) void unityOutputStart(void) { Serial.begin(115200); }
extern "C" __attribute__((weak)) void unityOutputChar(char c) { Serial.write(static_cast<uint8_t>(c)); }
extern "C" __attribute__((weak)) void unityOutputFlush(void) { Serial.flush(); }
extern "C" __attribute__((weak)) void unityOutputComplete(void) {}
