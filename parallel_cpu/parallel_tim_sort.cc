#include "parallel_tim_sort.h"
#include "../single_cpu/merge_sort.h"
#include "../single_cpu/tim_sort.h"
#include <thread>

namespace rr::parallel_cpu {
// this is the minimum size of the vector to be sorted in parallel
constexpr int kMinParallelSize = 2048;

void parallel_tim_sort(std::vector<std::string>::iterator begin,
                       std::vector<std::string>::iterator end) {
  if (end - begin <= kMinParallelSize) {
    rr::single_cpu::tim_sort(begin, end);
    return;
  }

  auto mid = begin + (end - begin) / 2;
  auto thread = std::thread(parallel_tim_sort, begin, mid);

  parallel_tim_sort(mid, end);

  thread.join();

  rr::single_cpu::merge(begin, mid, end);
}
} // namespace rr::parallel_cpu