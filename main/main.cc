#include "../parallel_cpu/parallel_merge_sort.h"
#include "../single_cpu/merge_sort.h"
#include "../utils/benchmark/sort_benchmark.h"
#include <algorithm>
#include <functional>
#include <iostream>

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
      TestData("long", long_repeated, long_repeated, 10),
  };

  auto test_algorithms = std::vector<SortAlgorithm>{
      SortAlgorithm("single_cpu::merge_sort", rr::single_cpu::merge_sort),
      SortAlgorithm("parallel_cpu::parallel_merge_sort",
                    rr::parallel_cpu::parallel_merge_sort),
  };

  for (const auto &data : test_data) {
    for (const auto &algo : test_algorithms) {
      std::cout << "Running " << algo.name << " on " << data.name << std::endl;
      auto result =
          rr::utils::SortBenchmark(data.name, algo.name, algo.sort_function,
                                   data.data, data.correct, data.iterations)
              .run();
      std::cout << result.to_string() << std::endl;
    }
  }

  return 0;
}
