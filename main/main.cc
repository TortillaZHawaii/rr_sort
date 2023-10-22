#include "../single_cpu/merge_sort.h"
#include "../utils/benchmark/benchmark.h"
#include <iostream>

int main() {
  std::cout << "Hello, world!" << std::endl;
  const std::vector<std::string> data{"hello", "world", "this",     "is",
                                      "a",     "test",  "of",       "the",
                                      "merge", "sort",  "algorithm"};

  std::vector<std::string> data_copy = data;

  rr::single_cpu::merge_sort(data_copy.begin(), data_copy.end());

  // auto result =
  //     rr::utils::Benchmark(
  //         "Small data", "single_cpu::merge_sort",
  //         [&]() {
  //           rr::single_cpu::merge_sort(data_copy.begin(), data_copy.end());
  //         },
  //         10)
  //         .run();

  // std::cout << result.to_string() << std::endl;

  for (const auto &s : data_copy) {
    std::cout << s << " ";
  }
  std::cout << std::endl;

  return 0;
}
