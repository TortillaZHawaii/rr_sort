#include "benchmark_result.h"

namespace rr::utils {

std::string BenchmarkResult::to_string() const {
  std::string result = "Benchmark result:\n";
  result += "Data name: " + data_name + "\n";
  result += "Algorithm name: " + algorithm_name + "\n";
  result += "Correct runs: " + std::to_string(number_of_correct_runs) +
            " out of " + std::to_string(number_of_runs) + "\n";
  result +=
      "Is correct: " +
      std::string(number_of_correct_runs == number_of_runs ? "yes" : "no") +
      "\n";
  result += "Min time: " + std::to_string(min_time_ns) + " ns\n";

  result += "Max time: " + std::to_string(max_time_ns) + " ns\n";
  result +=
      "Standard deviation: " + std::to_string(standard_deviation_ns) + " ns\n";
  result += "Average time: " + std::to_string(average_time_ns) + " ns\n";
  return result;
}

std::string BenchmarkResult::to_csv() const {
  std::string result =
      data_name + "," + algorithm_name + "," + std::to_string(number_of_runs) +
      "," + std::to_string(number_of_correct_runs) + "," +
      std::to_string(min_time_ns) + "," + std::to_string(max_time_ns) + "," +
      std::to_string(standard_deviation_ns) + "," +
      std::to_string(average_time_ns);
  return result;
}

std::string BenchmarkResult::csv_header() {
  return "data_name,algorithm_name,number_of_runs,number_of_correct_runs,"
         "min_time_ns,max_time_ns,standard_deviation_ns,average_time_ns";
}
} // namespace rr::utils