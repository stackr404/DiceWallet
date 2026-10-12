#pragma once

#include "dice/die_fairness.h"

// ui_new_wallet_warning
// Shown when chi-square passed and at least one other fairness test failed.
// Each row is green on pass, red on fail.
// Buttons: "Start Again" (clear rolls, return to roll step)
//          "Proceed"     (continue the wallet flow)

struct warning_row {
  const char* name;
  bool passed;  // true = green Pass, false = red Fail
};

// Fills out[0..6] in display order. Returns 7.
int build_warning_rows(const fairness_report& report, warning_row out[7]);

// Screen entry point. Implement against the existing UI toolkit.
void open_new_wallet_warning(const fairness_report& report);