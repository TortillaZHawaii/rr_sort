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

  return 0;
}
