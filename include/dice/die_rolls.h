#pragma once

// Accepted d6 rolls for a 24-word seed. 100 is the fair-die minimum.
// 128 is the default: it still covers a board-game die with a hot face.
// 200 is the slider maximum and the roll-buffer size.
static constexpr int k_min_die_rolls = 100;
static constexpr int k_default_die_rolls = 128;
static constexpr int k_max_die_rolls = 200;
