#include "../parallel_cpu/parallel_merge_sort.h"
#include "../single_cpu/merge_sort.h"
#include "../utils/benchmark/sort_benchmark.h"
#include <algorithm>
#include <iostream>

int main() {
  std::cout << "Hello, world!" << std::endl;
  const std::vector<std::string> data{"hello", "world", "this",     "is",
                                      "a",     "test",  "of",       "the",
                                      "merge", "sort",  "algorithm"};

  const std::vector<std::string> correct{"a",     "algorithm", "hello", "is",
                                         "merge", "of",        "sort",  "test",
                                         "the",   "this",      "world"};

  auto result =
      rr::utils::SortBenchmark("test_data", "single_cpu::merge_sort",
                               rr::single_cpu::merge_sort, data, correct, 1000)
          .run();

  std::cout << result.to_string() << std::endl;

  auto result_paralllel =
      rr::utils::SortBenchmark("test_data", "parallel_cpu::parallel_merge_sort",
                               rr::parallel_cpu::parallel_merge_sort, data,
                               correct, 1000)
          .run();

  std::cout << result_paralllel.to_string() << std::endl;

  return 0;
}
