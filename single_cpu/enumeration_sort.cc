#include "enumeration_sort.h"

namespace rr::single_cpu {
void enumeration_sort(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
  std::vector<int> ranks(end - begin);

  for (auto i = begin; i != end; ++i) {
    auto rank = 0;
    for (auto j = begin; j != end; ++j) {
      if (j == i) {
        continue;
      }

      if (*j < *i || (*j == *i && j < i)) {
        ++rank;
      }
    }
    ranks[i - begin] = rank;
  }

  std::vector<std::string> sorted(end - begin);
  for (auto i = 0; i < ranks.size(); ++i) {
    sorted[i] = *(begin + ranks[i]);
  }
  // copy back
  for (auto i = 0; i < sorted.size(); ++i) {
    *(begin + i) = sorted[i];
  }
}
} // namespace rr::single_cpu