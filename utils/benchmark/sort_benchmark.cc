#include "sort_benchmark.h"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <iostream>

namespace rr::utils {

bool is_correct(const std::vector<std::string> data,
                const std::vector<std::string> correct) {
  if (data.size() != correct.size()) {
    std::cerr << "Data size is not correct\n" << std::endl;
    return false;
  }
  for (size_t i = 0; i < data.size(); ++i) {
    if (data[i] != correct[i]) {
      std::cerr << "Data is not correct at " << i << " " << data[i]
                << " != " << correct[i] << std::endl;
      return false;
    }
  }
  return true;
}

BenchmarkResult SortBenchmark::run() const {
  std::vector<double> run_times;
  int correct_runs = 0;
  run_times.reserve(number_of_runs);

  for (int i = 0; i < number_of_runs; ++i) {
    std::vector<std::string> data_copy(data);
    auto start_time = std::chrono::high_resolution_clock::now();
    algorithm(data_copy.begin(), data_copy.end());
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                           end_time - start_time)
                           .count();
    run_times.push_back(static_cast<double>(duration_ns));
    if (is_correct(data_copy, after_sort_data)) {
      ++correct_runs;
    }
  }

  // Calculate statistics
  double max_time = run_times[0];
  double min_time = run_times[0];
  double sum = 0.0;
  for (double time : run_times) {
    sum += time;
    max_time = std::max(max_time, time);
    min_time = std::min(min_time, time);
  }
  double average_time = sum / static_cast<double>(number_of_runs);
  double standard_deviation = 0.0;
  for (double time : run_times) {
    standard_deviation += std::pow(time - average_time, 2);
  }
  standard_deviation =
      std::sqrt(standard_deviation / static_cast<double>(number_of_runs));

  return BenchmarkResult(data_name, algorithm_name, number_of_runs,
                         correct_runs, max_time, average_time,
                         standard_deviation, min_time);
}

} // namespace rr::utils
