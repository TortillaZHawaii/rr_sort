#pragma once

#include "benchmark_result.h"
#include <functional>
#include <string>
#include <vector>

namespace rr::utils {
using SortingAlgorithm = std::function<void(
    std::vector<std::string>::iterator, std::vector<std::string>::iterator)>;

class SortBenchmark {
  std::string data_name;
  std::string algorithm_name;
  SortingAlgorithm algorithm;
  const std::vector<std::string> &data;
  const std::vector<std::string> &after_sort_data;
  int number_of_runs;

public:
  SortBenchmark(std::string data_name, std::string algorithm_name,
                SortingAlgorithm algorithm,
                const std::vector<std::string> &data,
                const std::vector<std::string> &after_sort_data,
                int number_of_runs)
      : data_name(data_name), algorithm_name(algorithm_name),
        algorithm(algorithm), data(data), after_sort_data(after_sort_data),
        number_of_runs(number_of_runs) {}

  BenchmarkResult run() const;
};
} // namespace rr::utils
