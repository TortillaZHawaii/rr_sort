#include "../parallel_cpu/parallel_intro_sort.h"
#include "../parallel_cpu/parallel_merge_sort.h"
#include "../single_cpu/insertion_sort.h"
#include "../single_cpu/intro_sort.h"
#include "../single_cpu/merge_sort.h"
#include "../utils/benchmark/sort_benchmark.h"
#include <algorithm>
// #include <execution>
#include <functional>
#include <iostream>
#include <sstream>

struct TestData {
  const std::string name;
  const std::vector<std::string> data;
  const std::vector<std::string> correct;
  const int iterations;

  TestData(const std::string &name, const std::vector<std::string> &data,
           const std::vector<std::string> &correct, const int &iterations)
      : name(name), data(data), correct(correct), iterations(iterations) {}
};

struct SortAlgorithm {
  using SortFunction = std::function<void(std::vector<std::string>::iterator,
                                          std::vector<std::string>::iterator)>;
  const std::string name;
  const SortFunction sort_function;

  SortAlgorithm(const std::string &name, const SortFunction &sort_function)
      : name(name), sort_function(sort_function) {}
};

int main() {
  const std::vector<std::string> data{"hello", "world", "this",     "is",
                                      "a",     "test",  "of",       "the",
                                      "merge", "sort",  "algorithm"};

  const std::vector<std::string> correct{"a",     "algorithm", "hello", "is",
                                         "merge", "of",        "sort",  "test",
                                         "the",   "this",      "world"};

  const std::vector<std::string> long_repeated(18000, "hello");

  auto test_data = std::vector<TestData>{
      TestData("short", data, correct, 1000),
      TestData("long_repeated", long_repeated, long_repeated, 100),
  };

  auto test_algorithms = std::vector<SortAlgorithm>{
      SortAlgorithm("single_cpu::merge_sort", rr::single_cpu::merge_sort),
      SortAlgorithm("parallel_cpu::parallel_merge_sort",
                    rr::parallel_cpu::parallel_merge_sort),
      SortAlgorithm("std::sort",
                    [](auto begin, auto end) { std::sort(begin, end); }),
      SortAlgorithm("single_cpu::insertion_sort",
                    rr::single_cpu::insertion_sort),
      SortAlgorithm("single_cpu::intro_sort", rr::single_cpu::intro_sort),
      SortAlgorithm("parallel_cpu::parallel_intro_sort",
                    rr::parallel_cpu::parallel_intro_sort),
      // SortAlgorithm("std::sort parallel mode",
      //               [](auto begin, auto end) {
      //                 std::sort(std::execution::par_seq, begin, end);
      //               }),
  };

  std::stringstream csv;
  csv << rr::utils::BenchmarkResult::csv_header() << std::endl;

  for (const auto &data : test_data) {
    for (const auto &algo : test_algorithms) {
      std::cout << "Running " << algo.name << " on " << data.name << std::endl;
      auto result =
          rr::utils::SortBenchmark(data.name, algo.name, algo.sort_function,
                                   data.data, data.correct, data.iterations)
              .run();
      std::cout << result << std::endl;
      csv << result.to_csv() << std::endl;
    }
  }

  std::cout << csv.str() << std::endl;

  return 0;
}
