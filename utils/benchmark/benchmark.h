#pragma once

#include "benchmark_result.h"
#include <functional>
#include <string>
#include <vector>

namespace rr::utils {
class Benchmark {
  std::string data_name;
  std::string algorithm_name;
  std::function<void()> algorithm;
  int number_of_runs;

public:
  Benchmark(std::string data_name, std::string algorithm_name,
            std::function<void()> algorithm, int number_of_runs)
      : data_name(data_name), algorithm_name(algorithm_name),
        algorithm(algorithm), number_of_runs(number_of_runs) {}

  BenchmarkResult run() const;
};
} // namespace rr::utils
