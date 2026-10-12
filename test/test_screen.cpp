#include <TFT_eSPI.h>

#include "test_screen.h"

namespace {
constexpr int kMaxResults = 16;
constexpr int kNameChars = 28;

struct Result {
  char name[kNameChars + 1];
  bool passed;
};

TFT_eSPI tft;
bool ready = false;
char header[48] = "";
Result results[kMaxResults];
int result_count = 0;

void ensure_ready(void) {
  if (ready) return;
  tft.init();
  tft.setRotation(0);
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, TFT_BACKLIGHT_ON);
  ready = true;
}

void copy_name(char *out, const char *name) {
  int i = 0;
  if (name != nullptr) {
    for (; i < kNameChars && name[i] != '\0'; ++i) out[i] = name[i];
  }
  out[i] = '\0';
}

void draw(void) {
  ensure_ready();
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setCursor(4, 8);
  tft.println(header);

  for (int i = 0; i < result_count; ++i) {
    const int y = 28 + i * 16;
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(4, y);
    tft.print(results[i].name);
    tft.setTextColor(results[i].passed ? TFT_GREEN : TFT_RED, TFT_BLACK);
    tft.setCursor(188, y);
    tft.print(results[i].passed ? "PASS" : "FAIL");
  }
}
}

void test_show_name(const char *name) {
  result_count = 0;
  copy_name(header, name);
  draw();
}

void test_show_result(const char *name, bool passed) {
  if (result_count < kMaxResults) {
    copy_name(results[result_count].name, name);
    results[result_count].passed = passed;
    result_count++;
  }
  draw();
}