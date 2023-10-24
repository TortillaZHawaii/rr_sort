#pragma once

#include <string>

namespace rr::utils {
class BenchmarkResult {
  std::string data_name;
  std::string algorithm_name;
  int number_of_runs;
  int number_of_correct_runs;
  double max_time_ns;
  double average_time_ns;
  double standard_deviation_ns;
  double min_time_ns;

public:
  BenchmarkResult(std::string data_name, std::string algorithm_name,
                  int number_of_runs, int number_of_correct_runs,
                  double max_time_ns, double average_time_ns,
                  double standard_deviation_ns, double min_time_ns)
      : data_name(data_name), algorithm_name(algorithm_name),
        number_of_runs(number_of_runs),
        number_of_correct_runs(number_of_correct_runs),
        max_time_ns(max_time_ns), average_time_ns(average_time_ns),
        standard_deviation_ns(standard_deviation_ns), min_time_ns(min_time_ns) {
  }

  std::string get_data_name() const { return data_name; }
  std::string get_algorithm_name() const { return algorithm_name; }
  int get_number_of_runs() const { return number_of_runs; }
  int get_number_of_correct_runs() const { return number_of_correct_runs; }
  double get_max_time_ns() const { return max_time_ns; }
  double get_average_time_ns() const { return average_time_ns; }
  double get_standard_deviation_ns() const { return standard_deviation_ns; }
  double get_min_time_ns() const { return min_time_ns; }

  std::string to_string() const;

  operator std::string() const { return to_string(); }

  friend std::ostream &operator<<(std::ostream &os,
                                  const BenchmarkResult &result) {
    os << result.to_string();
    return os;
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const BenchmarkResult *result) {
    os << result->to_string();
    return os;
  }

  std::string to_csv() const;

  static std::string csv_header();
};
} // namespace rr::utils
