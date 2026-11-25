#include "dice/die_fairness.h"

#include <cmath>
#include <algorithm>

// Chi-square critical value at 5% (the blocking chi test) for df = 5.
static constexpr float kChi5Df5 = 11.0705f;

// The six warning tests each use a 1% level, so honest dice trigger a warning
// about 5% of the time in total. At 5% each (plus a mis-calibrated serial test)
// honest dice were warned about 35-38% of the time, which teaches people to
// ignore the warning. Rates are checked by the simulation in test_dice.
static constexpr float kZ1 = 2.5758f;           // two-sided 1% normal
static constexpr float kChi1Df3 = 11.3449f;     // poker, 4 pooled classes
static constexpr float kChi1Df30 = 50.8922f;    // serial (Good's statistic), 36 - 6

static int face_index(int face) {
  if (face < 1) return 0;
  if (face > 6) return 5;
  return face - 1;
}

chi_result calculate_chi_square(const int* roll_sequence, int total_rolls) {
  chi_result r{};
  r.critical_value = kChi5Df5;
  r.expected_per_face = total_rolls > 0 ? static_cast<float>(total_rolls) / 6.0f : 0.0f;
  if (total_rolls <= 0 || roll_sequence == nullptr || r.expected_per_face <= 0.0f) {
    r.is_fair = false;
    return r;
  }
  for (int i = 0; i < total_rolls; ++i) {
    r.observed_counts[face_index(roll_sequence[i])] += 1.0f;
  }
  float chi = 0.0f;
  for (int f = 0; f < 6; ++f) {
    const float d = r.observed_counts[f] - r.expected_per_face;
    chi += (d * d) / r.expected_per_face;
  }
  r.chi_squared_score = chi;
  r.is_fair = chi <= r.critical_value;
  return r;
}

runs_result calculate_runs_test(const int* roll_sequence, int total_rolls) {
  // Wald–Wolfowitz on high (4-6) vs low (1-3). Too few runs => human-faked streaks.
  runs_result r{};
  if (total_rolls < 2 || roll_sequence == nullptr) {
    r.is_human_faked = true;
    return r;
  }
  int n_high = 0;
  int n_low = 0;
  int runs = 1;
  bool prev_high = roll_sequence[0] >= 4;
  if (prev_high) ++n_high; else ++n_low;
  for (int i = 1; i < total_rolls; ++i) {
    const bool high = roll_sequence[i] >= 4;
    if (high) ++n_high; else ++n_low;
    if (high != prev_high) {
      ++runs;
      prev_high = high;
    }
  }
  r.total_runs = runs;
  const float n1 = static_cast<float>(n_high);
  const float n2 = static_cast<float>(n_low);
  const float n = n1 + n2;
  if (n1 == 0.0f || n2 == 0.0f || n < 2.0f) {
    r.is_human_faked = true;
    r.z_score = -99.0f;
    return r;
  }
  const float expected = (2.0f * n1 * n2) / n + 1.0f;
  const float variance = (2.0f * n1 * n2 * (2.0f * n1 * n2 - n)) / (n * n * (n - 1.0f));
  const float sd = variance > 0.0f ? std::sqrt(variance) : 1.0f;
  r.z_score = (static_cast<float>(runs) - expected) / sd;
  // Two-sided 1%. Negative z is the human-streak case; either tail fails.
  r.is_human_faked = std::fabs(r.z_score) > kZ1;
  return r;
}

serial_result calculate_serial_correlation(const int* roll_sequence, int total_rolls) {
  // Good's serial test. The pairs overlap, so the plain 6x6 pair chi-square is
  // not chi-square distributed (with ~3 expected per cell at n=100 it failed
  // honest dice ~35% of the time). Good's statistic, pair chi-square minus
  // single-face chi-square over the same n-1 positions, is chi-square with
  // 36 - 6 = 30 degrees of freedom.
  serial_result r{};
  r.critical_value = kChi1Df30;
  if (total_rolls < 2 || roll_sequence == nullptr) {
    r.has_pattern_bias = true;
    return r;
  }
  const int pairs = total_rolls - 1;
  int counts[6][6] = {};
  for (int i = 0; i < pairs; ++i) {
    counts[face_index(roll_sequence[i])][face_index(roll_sequence[i + 1])] += 1;
  }
  // Count pairs cyclically (last roll wraps to the first) so every face
  // appears equally often as first and second element; Good's theorem uses this.
  counts[face_index(roll_sequence[total_rolls - 1])][face_index(roll_sequence[0])] += 1;
  const int n = total_rolls;
  int singles[6] = {};
  for (int i = 0; i < n; ++i) singles[face_index(roll_sequence[i])] += 1;
  const float e2 = static_cast<float>(n) / 36.0f;
  const float e1 = static_cast<float>(n) / 6.0f;
  float psi2 = 0.0f;
  for (int a = 0; a < 6; ++a) {
    for (int b = 0; b < 6; ++b) {
      const float d = static_cast<float>(counts[a][b]) - e2;
      psi2 += (d * d) / e2;
    }
  }
  float psi1 = 0.0f;
  for (int a = 0; a < 6; ++a) {
    const float d = static_cast<float>(singles[a]) - e1;
    psi1 += (d * d) / e1;
  }
  const float chi = psi2 - psi1;
  r.chi_square_serial = chi;
  r.has_pattern_bias = chi > r.critical_value;
  return r;
}

gap_result calculate_gap_test(const int* roll_sequence, int total_rolls) {
  // Gaps between repeats of the same face. Geometric(1/6) has mean 6, variance 30.
  // Too-small variance means the gaps are unnaturally regular.
  gap_result r{};
  if (total_rolls < 2 || roll_sequence == nullptr) {
    r.is_too_uniform = true;
    return r;
  }
  int last[6];
  for (int f = 0; f < 6; ++f) last[f] = -1;
  float sum = 0.0f;
  float sum_sq = 0.0f;
  int n_gaps = 0;
  for (int i = 0; i < total_rolls; ++i) {
    const int f = face_index(roll_sequence[i]);
    if (last[f] >= 0) {
      const float gap = static_cast<float>(i - last[f]);
      sum += gap;
      sum_sq += gap * gap;
      ++n_gaps;
    }
    last[f] = i;
  }
  if (n_gaps < 2) {
    r.is_too_uniform = true;
    return r;
  }
  r.average_gap = sum / static_cast<float>(n_gaps);
  const float mean = r.average_gap;
  r.gap_variance = sum_sq / static_cast<float>(n_gaps) - mean * mean;
  // Expected variance for geometric waits of 6 is 30. Flag if variance is under half
  // of that, or the mean is far from 6 (more than ~2 se).
  const float se = std::sqrt(30.0f / static_cast<float>(n_gaps));
  const bool mean_off = std::fabs(r.average_gap - 6.0f) > kZ1 * se;
  const bool var_low = r.gap_variance < 15.0f;
  // People inventing rolls avoid repeating the last face. A fair die repeats
  // with probability 1/6. One-sided 0.5% test on the repeat count.
  int repeats = 0;
  for (int i = 1; i < total_rolls; ++i) {
    if (roll_sequence[i] == roll_sequence[i - 1]) ++repeats;
  }
  const float pairs = static_cast<float>(total_rolls - 1);
  const float expected_repeats = pairs / 6.0f;
  const float sd_repeats = std::sqrt(pairs * (1.0f / 6.0f) * (5.0f / 6.0f));
  r.immediate_repeats = repeats;
  r.repeat_z = (static_cast<float>(repeats) - expected_repeats) / sd_repeats;
  const bool too_few_repeats = r.repeat_z < -kZ1;
  r.is_too_uniform = mean_off || var_low || too_few_repeats;
  return r;
}

longest_run_result calculate_longest_run(const int* roll_sequence, int total_rolls) {
  longest_run_result r{};
  if (total_rolls <= 0 || roll_sequence == nullptr) {
    r.is_suspicious = true;
    return r;
  }
  int high = 0, low = 0, same = 0;
  for (int i = 0; i < total_rolls; ++i) {
    const bool is_high = roll_sequence[i] >= 4;
    if (i == 0 || is_high != (roll_sequence[i - 1] >= 4)) {
      high = is_high ? 1 : 0;
      low = is_high ? 0 : 1;
    } else if (is_high) {
      ++high;
    } else {
      ++low;
    }
    if (i == 0 || roll_sequence[i] != roll_sequence[i - 1]) same = 1;
    else ++same;
    r.longest_high_run = std::max(r.longest_high_run, high);
    r.longest_low_run = std::max(r.longest_low_run, low);
    r.longest_same_face = std::max(r.longest_same_face, same);
  }
  // Limits for about a 0.5% false alarm rate over 100-200 rolls (simulated):
  // a high/low run of 15 has P ~0.3% at n=100; 16 has P ~0.3% at n=200.
  // A same-face run of 7 has P ~0.2-0.35% over 100-200 rolls.
  const int hl_limit = total_rolls <= 120 ? 15 : 16;
  r.is_suspicious = r.longest_high_run >= hl_limit || r.longest_low_run >= hl_limit ||
                    r.longest_same_face >= 7;
  return r;
}

poker_result calculate_poker_test(const int* roll_sequence, int total_rolls) {
  // Non-overlapping hands of 5. Classes by pattern of face multiplicities:
  // 0 all different, 1 one pair, 2 two pair, 3 three of a kind, 4 full house,
  // 5 four of a kind, 6 five of a kind.
  poker_result r{};
  r.critical_value = kChi1Df3;
  const int hands = total_rolls / 5;
  if (hands < 1 || roll_sequence == nullptr) {
    r.is_suspicious = true;
    return r;
  }
  for (int h = 0; h < hands; ++h) {
    int freq[6] = {};
    for (int k = 0; k < 5; ++k) freq[face_index(roll_sequence[h * 5 + k])] += 1;
    int pairs = 0, trips = 0, quads = 0, fives = 0;
    for (int f = 0; f < 6; ++f) {
      if (freq[f] == 2) ++pairs;
      else if (freq[f] == 3) ++trips;
      else if (freq[f] == 4) ++quads;
      else if (freq[f] == 5) ++fives;
    }
    int cls = 0;
    if (fives) cls = 6;
    else if (quads) cls = 5;
    else if (trips && pairs) cls = 4;
    else if (trips) cls = 3;
    else if (pairs == 2) cls = 2;
    else if (pairs == 1) cls = 1;
    else cls = 0;
    r.hand_counts[cls] += 1;
  }
  // Multinomial probabilities for 5 dice, 6 faces.
  const float p[7] = {
    0.0925926f,  // all different: 6/6*5/6*4/6*3/6*2/6
    0.4629630f,  // one pair
    0.2314815f,  // two pair
    0.1543209f,  // three of a kind
    0.0385802f,  // full house
    0.0192901f,  // four of a kind
    0.0007716f   // five of a kind
  };
  // With 20-40 hands the rare classes expect fewer than one hand each, so pool
  // three-of-a-kind, full house, four and five of a kind into one class:
  // 4 classes, df = 3. (Skipping them instead left the df wrong.)
  const float pooled_p[4] = {p[0], p[1], p[2], p[3] + p[4] + p[5] + p[6]};
  const int pooled_counts[4] = {
    r.hand_counts[0], r.hand_counts[1], r.hand_counts[2],
    r.hand_counts[3] + r.hand_counts[4] + r.hand_counts[5] + r.hand_counts[6]};
  float chi = 0.0f;
  const float n = static_cast<float>(hands);
  for (int c = 0; c < 4; ++c) {
    const float expected = pooled_p[c] * n;
    const float d = static_cast<float>(pooled_counts[c]) - expected;
    chi += (d * d) / expected;
  }
  r.chi_squared = chi;
  r.is_suspicious = chi > r.critical_value;
  return r;
}

auto_corr_result calculate_autocorrelation(const int* roll_sequence, int total_rolls) {
  // Lag-1 Pearson correlation. Independent dice => r near 0; se ≈ 1/sqrt(n).
  auto_corr_result r{};
  if (total_rolls < 3 || roll_sequence == nullptr) {
    r.is_dependent = true;
    return r;
  }
  const int n = total_rolls - 1;
  double sum_x = 0.0, sum_y = 0.0, sum_xx = 0.0, sum_yy = 0.0, sum_xy = 0.0;
  for (int i = 0; i < n; ++i) {
    const double x = static_cast<double>(roll_sequence[i]);
    const double y = static_cast<double>(roll_sequence[i + 1]);
    sum_x += x;
    sum_y += y;
    sum_xx += x * x;
    sum_yy += y * y;
    sum_xy += x * y;
  }
  const double nd = static_cast<double>(n);
  const double num = nd * sum_xy - sum_x * sum_y;
  const double den_x = nd * sum_xx - sum_x * sum_x;
  const double den_y = nd * sum_yy - sum_y * sum_y;
  const double den = std::sqrt(std::max(0.0, den_x * den_y));
  r.correlation = den > 0.0 ? static_cast<float>(num / den) : 0.0f;
  r.critical_value = kZ1 / std::sqrt(static_cast<float>(total_rolls));
  r.is_dependent = std::fabs(r.correlation) > r.critical_value;
  return r;
}

bool chi_passed(const chi_result& r) { return r.is_fair; }
bool runs_passed(const runs_result& r) { return !r.is_human_faked; }
bool serial_passed(const serial_result& r) { return !r.has_pattern_bias; }
bool gap_passed(const gap_result& r) { return !r.is_too_uniform; }
bool longest_passed(const longest_run_result& r) { return !r.is_suspicious; }
bool poker_passed(const poker_result& r) { return !r.is_suspicious; }
bool autocorr_passed(const auto_corr_result& r) { return !r.is_dependent; }

fairness_report run_die_fairness_tests(const int* roll_sequence, int total_rolls) {
  fairness_report report;
  report.chi = calculate_chi_square(roll_sequence, total_rolls);
  report.runs = calculate_runs_test(roll_sequence, total_rolls);
  report.serial = calculate_serial_correlation(roll_sequence, total_rolls);
  report.gap = calculate_gap_test(roll_sequence, total_rolls);
  report.longest = calculate_longest_run(roll_sequence, total_rolls);
  report.poker = calculate_poker_test(roll_sequence, total_rolls);
  report.autocorr = calculate_autocorrelation(roll_sequence, total_rolls);
  return report;
}

fairness_verdict run_fairness_verdict(const fairness_report& report) {
  if (!chi_passed(report.chi)) return fairness_verdict::error;
  const bool others_ok =
      runs_passed(report.runs) &&
      serial_passed(report.serial) &&
      gap_passed(report.gap) &&
      longest_passed(report.longest) &&
      poker_passed(report.poker) &&
      autocorr_passed(report.autocorr);
  return others_ok ? fairness_verdict::success : fairness_verdict::warning;
}