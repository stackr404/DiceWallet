#include <Arduino.h>
#include <unity.h>
#include "../test_screen.h"
#include "dice/die_fairness.h"

static int sequence_a[] = {1, 1, 2, 2, 2, 3, 1, 6, 6, 4};

static void test_all_ones_is_chi_error(void) {
  int ones[100];
  for (int i = 0; i < 100; i++) ones[i] = 1;
  const chi_result chi = calculate_chi_square(ones, 100);
  TEST_ASSERT_FALSE(chi.is_fair);
  TEST_ASSERT_EQUAL_FLOAT(100.0f, chi.observed_counts[0]);
  TEST_ASSERT_FLOAT_WITHIN(0.01f, 11.0705f, chi.critical_value);
  const fairness_report report = run_die_fairness_tests(ones, 100);
  TEST_ASSERT_TRUE(run_fairness_verdict(report) == fairness_verdict::error);
  TEST_ASSERT_FALSE(chi_passed(report.chi));
  const longest_run_result longest = calculate_longest_run(ones, 100);
  TEST_ASSERT_EQUAL(100, longest.longest_same_face);
  TEST_ASSERT_TRUE(longest.is_suspicious);
}

static void test_balanced_counts_pass_chi(void) {
  int fair[100];
  int n = 0;
  const int counts[6] = {16, 16, 17, 17, 17, 17};
  for (int face = 1; face <= 6; face++) {
    for (int c = 0; c < counts[face - 1]; c++) fair[n++] = face;
  }
  TEST_ASSERT_EQUAL(100, n);
  const chi_result chi = calculate_chi_square(fair, 100);
  TEST_ASSERT_TRUE(chi.is_fair);
  TEST_ASSERT_TRUE(chi.chi_squared_score < chi.critical_value);
}

static void test_null_and_empty_are_not_fair(void) {
  int fair[1] = {1};
  const chi_result missing = calculate_chi_square(nullptr, 100);
  TEST_ASSERT_FALSE(missing.is_fair);
  const chi_result empty = calculate_chi_square(fair, 0);
  TEST_ASSERT_FALSE(empty.is_fair);
  const fairness_report report = run_die_fairness_tests(nullptr, 0);
  TEST_ASSERT_TRUE(run_fairness_verdict(report) != fairness_verdict::success);
}

static void test_round_robin_is_not_chi_error(void) {
  int mixed[100];
  for (int i = 0; i < 100; i++) mixed[i] = (i % 6) + 1;
  const fairness_report report = run_die_fairness_tests(mixed, 100);
  TEST_ASSERT_TRUE(chi_passed(report.chi));
  TEST_ASSERT_TRUE(run_fairness_verdict(report) != fairness_verdict::error);
  TEST_ASSERT_TRUE(report.chi.observed_counts[0] >= 16.0f);
  TEST_ASSERT_TRUE(report.chi.observed_counts[5] >= 16.0f);
}

static void test_longest_run_finds_length(void) {
  const longest_run_result result = calculate_longest_run(sequence_a, 10);
  TEST_ASSERT_EQUAL(3, result.longest_same_face);
  TEST_ASSERT_FALSE(result.is_suspicious);
}

static void test_alternating_sequence_has_no_repeated_face(void) {
  int alternating[100];
  for (int i = 0; i < 100; i++) alternating[i] = (i % 2 == 0) ? 1 : 6;
  const longest_run_result longest = calculate_longest_run(alternating, 100);
  TEST_ASSERT_EQUAL(1, longest.longest_same_face);
  TEST_ASSERT_EQUAL(1, longest.longest_high_run);
  TEST_ASSERT_EQUAL(1, longest.longest_low_run);
  TEST_ASSERT_FALSE(longest.is_suspicious);
}

static void test_long_low_run_is_suspicious(void) {
  int low[100];
  for (int i = 0; i < 100; i++) low[i] = (i % 2 == 0) ? 1 : 2;
  const longest_run_result longest = calculate_longest_run(low, 100);
  TEST_ASSERT_EQUAL(1, longest.longest_same_face);
  TEST_ASSERT_EQUAL(100, longest.longest_low_run);
  TEST_ASSERT_TRUE(longest.is_suspicious);
}

static void test_poker_score_is_non_negative(void) {
  int mixed[96];
  for (int i = 0; i < 96; i++) mixed[i] = (i % 6) + 1;
  const poker_result poker = calculate_poker_test(mixed, 96);
  TEST_ASSERT_TRUE(poker.chi_squared >= 0.0f);
}

static void test_report_matches_longest_run(void) {
  const fairness_report report = run_die_fairness_tests(sequence_a, 10);
  TEST_ASSERT_EQUAL(calculate_longest_run(sequence_a, 10).longest_same_face, report.longest.longest_same_face);
}

static void test_other_calculators_can_be_called(void) {
  const runs_result runs = calculate_runs_test(sequence_a, 10);
  const serial_result serial = calculate_serial_correlation(sequence_a, 10);
  const gap_result gap = calculate_gap_test(sequence_a, 10);
  const auto_corr_result autocorr = calculate_autocorrelation(sequence_a, 10);
  TEST_ASSERT_TRUE(&runs != nullptr);
  TEST_ASSERT_TRUE(&serial != nullptr);
  TEST_ASSERT_TRUE(&gap != nullptr);
  TEST_ASSERT_TRUE(&autocorr != nullptr);
}

static void test_biased_sequence_is_not_success(void) {
  int ones[100];
  for (int i = 0; i < 100; i++) ones[i] = 1;
  const fairness_report report = run_die_fairness_tests(ones, 100);
  TEST_ASSERT_TRUE(run_fairness_verdict(report) != fairness_verdict::success);
}

// Fixed-seed xorshift32 so the result is the same on every run and device.
static uint32_t s_xs = 0x9E3779B9u;
static int next_face(void) {
  for (;;) {
    s_xs ^= s_xs << 13;
    s_xs ^= s_xs >> 17;
    s_xs ^= s_xs << 5;
    const uint32_t v = s_xs >> 29;  // 0..7, reject 6 and 7 to stay unbiased
    if (v < 6) return static_cast<int>(v) + 1;
  }
}

// Honest dice must rarely see a warning, or users learn to ignore it.
// Expected about 4% warnings and 5% chi errors; the limits leave room for noise.
static void test_fair_dice_rarely_warn(void) {
  const int trials = 300;
  int warnings = 0;
  int errors = 0;
  int rolls[128];
  for (int t = 0; t < trials; t++) {
    for (int i = 0; i < 128; i++) rolls[i] = next_face();
    const fairness_verdict v = run_fairness_verdict(run_die_fairness_tests(rolls, 128));
    if (v == fairness_verdict::warning) warnings++;
    if (v == fairness_verdict::error) errors++;
  }
  TEST_ASSERT_LESS_THAN_INT(trials * 8 / 100, warnings);
  TEST_ASSERT_LESS_THAN_INT(trials * 10 / 100, errors);
}

// Typical made-up sequences must still be flagged.
static void test_faked_sequences_warn(void) {
  int rolls[120];
  for (int i = 0; i < 120; i++) rolls[i] = (i % 6) + 1;
  TEST_ASSERT_TRUE(run_fairness_verdict(run_die_fairness_tests(rolls, 120)) != fairness_verdict::success);

  int prev = 0;
  for (int i = 0; i < 120; i++) {
    int f;
    do { f = next_face(); } while (f == prev);  // a person avoiding repeats
    rolls[i] = f;
    prev = f;
  }
  TEST_ASSERT_TRUE(run_fairness_verdict(run_die_fairness_tests(rolls, 120)) != fairness_verdict::success);

  for (int i = 0; i < 120; i++) rolls[i] = (i % 2) ? ((i / 2) % 3) + 4 : ((i / 2) % 3) + 1;
  TEST_ASSERT_TRUE(run_fairness_verdict(run_die_fairness_tests(rolls, 120)) != fairness_verdict::success);
}

void setup() {
  delay(2000);
  test_show_name("test_dice.cpp");
  UNITY_BEGIN();

  RUN_TEST(test_all_ones_is_chi_error);
  test_show_result("all ones chi error", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_balanced_counts_pass_chi);
  test_show_result("balaced counts pass chi", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_null_and_empty_are_not_fair);
  test_show_result("null and empty are not fair", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_round_robin_is_not_chi_error);
  test_show_result("round robin is not chi error", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_longest_run_finds_length);
  test_show_result("longest run", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_alternating_sequence_has_no_repeated_face);
  test_show_result("alternating sequence", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_long_low_run_is_suspicious);
  test_show_result("long low run is suspicious", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_poker_score_is_non_negative);
  test_show_result("poker score is non negative", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_report_matches_longest_run);
  test_show_result("longest run", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_other_calculators_can_be_called);
  test_show_result("other calculators called", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_biased_sequence_is_not_success);
  test_show_result("biased sequence", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_fair_dice_rarely_warn);
  test_show_result("fair dice rarely warn", Unity.CurrentTestFailed == 0);

  RUN_TEST(test_faked_sequences_warn);
  test_show_result("faked sequences warn", Unity.CurrentTestFailed == 0);

  UNITY_END();
}

void loop() {}
