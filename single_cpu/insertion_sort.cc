#include "insertion_sort.h"

namespace rr::single_cpu {
void insertion_sort(std::vector<std::string>::iterator begin,
                    std::vector<std::string>::iterator end) {
  for (auto i = begin; i != end; ++i) {
    auto key = *i;
    auto j = i - 1;
    while (j >= begin && *j > key) {
      *(j + 1) = *j;
      --j;
    }
    *(j + 1) = key;
  }
}

} // namespace rr::single_cpu
