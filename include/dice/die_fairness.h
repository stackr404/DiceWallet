#pragma once

// Die fairness checks for a sequence of face values in 1..6.
// Call after 100 rolls, before new_wallet_confirm.

struct chi_result {
  bool  is_fair;
  float chi_squared_score;
  float critical_value;
  float expected_per_face;
  float observed_counts[6];
};

struct runs_result {
  bool  is_human_faked;
  int   total_runs;
  float z_score;
};

struct serial_result {
  bool  has_pattern_bias;
  float chi_square_serial;
  float critical_value;
};

struct gap_result {
  bool  is_too_uniform;
  float average_gap;
  float gap_variance;
};

struct longest_run_result {
  bool  is_suspicious;
  int   longest_high_run;
  int   longest_low_run;
  int   longest_same_face;
};

struct poker_result {
  bool  is_suspicious;
  float chi_squared;
  float critical_value;
  int   hand_counts[7];
};

struct auto_corr_result {
  bool  is_dependent;
  float correlation;
  float critical_value;
};

struct fairness_report {
  chi_result         chi;
  runs_result        runs;
  serial_result      serial;
  gap_result         gap;
  longest_run_result longest;
  poker_result       poker;
  auto_corr_result   autocorr;
};

enum class fairness_verdict {
  success,  // every test passed -> new_wallet_confirm shows success
  warning,  // chi passed, some other test failed -> ui_new_wallet_warning
  error     // chi_result.is_fair == false -> error; Continue returns to main menu
};

chi_result         calculate_chi_square(const int* roll_sequence, int total_rolls);
runs_result        calculate_runs_test(const int* roll_sequence, int total_rolls);
serial_result      calculate_serial_correlation(const int* roll_sequence, int total_rolls);
gap_result         calculate_gap_test(const int* roll_sequence, int total_rolls);
longest_run_result calculate_longest_run(const int* roll_sequence, int total_rolls);
poker_result       calculate_poker_test(const int* roll_sequence, int total_rolls);
auto_corr_result   calculate_autocorrelation(const int* roll_sequence, int total_rolls);

fairness_report    run_die_fairness_tests(const int* roll_sequence, int total_rolls);
fairness_verdict   run_fairness_verdict(const fairness_report& report);

// Failure flags (true == that test failed). is_fair is inverted: pass when true.
bool chi_passed(const chi_result& r);
bool runs_passed(const runs_result& r);
bool serial_passed(const serial_result& r);
bool gap_passed(const gap_result& r);
bool longest_passed(const longest_run_result& r);
bool poker_passed(const poker_result& r);
bool autocorr_passed(const auto_corr_result& r);