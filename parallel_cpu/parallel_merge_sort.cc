#include "parallel_merge_sort.h"
#include "../single_cpu/merge_sort.h"
#include <thread>

namespace rr::parallel_cpu {
// this is the minimum size of the vector to be sorted in parallel
//
// smaller vectors are sorted in a single thread
//
// this is a tradeoff between the overhead of creating a new thread
constexpr int kMinParallelSize = 2048;

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