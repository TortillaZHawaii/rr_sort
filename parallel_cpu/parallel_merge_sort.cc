#include "parallel_merge_sort.h"
#include "../single_cpu/merge_sort.h"
#include <thread>

namespace rr::parallel_cpu {
constexpr int kMinParallelSize = 16;

void parallel_merge_sort(std::vector<std::string>::iterator begin,
                         std::vector<std::string>::iterator end) {
  if (end - begin <= kMinParallelSize) {
    rr::single_cpu::merge_sort(begin, end);
    return;
  }

  auto mid = begin + (end - begin) / 2;
  auto thread = std::thread(parallel_merge_sort, begin, mid);

  parallel_merge_sort(mid, end);

  thread.join();

  rr::single_cpu::merge(begin, mid, end);
}
} // namespace rr::parallel_cpu