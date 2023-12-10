#include "tim_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include <vector>

namespace rr::single_cpu {
const int kInsertionSortThreshold = 16;
void tim_sort(std::vector<std::string>::iterator begin,
              std::vector<std::string>::iterator end) {
  if (end - begin < kInsertionSortThreshold) {
    insertion_sort(begin, end);
    return;
  }

  auto mid = begin + (end - begin) / 2;
  tim_sort(begin, mid);
  tim_sort(mid, end);
  merge(begin, mid, end);
}
} // namespace rr::single_cpu