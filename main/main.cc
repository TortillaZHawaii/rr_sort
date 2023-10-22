#include "../utils/benchmark/benchmark.h"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
  std::cout << "Hello, world!" << std::endl;
  auto benchmark = rr::utils::Benchmark(
      "No data", "Just wait",
      []() { std::this_thread::sleep_for(std::chrono::seconds(1)); }, 3);

  auto result = benchmark.run();

  std::cout << result.to_string() << std::endl;
  return 0;
}
