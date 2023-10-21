#include "benchmark.h"
#include <chrono>
#include <cmath>
#include <iostream>

namespace rr::utils {

BenchmarkResult Benchmark::run() const {
  std::vector<double> run_times;
  run_times.reserve(number_of_runs);

  for (int i = 0; i < number_of_runs; ++i) {
    auto start_time = std::chrono::high_resolution_clock::now();
    algorithm();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                           end_time - start_time)
                           .count();
    run_times.push_back(static_cast<double>(duration_ns));
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

  return BenchmarkResult(data_name, algorithm_name, number_of_runs, max_time,
                         average_time, standard_deviation, min_time);
}

} // namespace rr::utils
