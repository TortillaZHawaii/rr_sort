#include "parallel_intro_sort.h"
#include "../single_cpu/intro_sort.h"
#include "../single_cpu/merge_sort.h"
#include <thread>

namespace rr::parallel_cpu {
// this is the minimum size of the vector to be sorted in parallel
constexpr int kMinParallelSize = 2048;

void parallel_intro_sort(std::vector<std::string>::iterator begin,
                         std::vector<std::string>::iterator end) {
  if (end - begin <= kMinParallelSize) {
    rr::single_cpu::intro_sort(begin, end);
    return;
  }

  auto mid = begin + (end - begin) / 2;
  auto thread = std::thread(parallel_intro_sort, begin, mid);

  parallel_intro_sort(mid, end);

  thread.join();

  rr::single_cpu::merge(begin, mid, end);
}
} // namespace rr::parallel_cpu