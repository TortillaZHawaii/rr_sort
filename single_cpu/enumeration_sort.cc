#include "enumeration_sort.h"
#include <iostream>

namespace rr::single_cpu {
void enumeration_sort(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
  int n = end - begin;
  std::vector<int> ranks(n);

  for (auto i = begin; i != end; ++i) {
    int rank = 0;
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

  std::vector<std::string> before(begin, end);
  for (int i = 0; i < ranks.size(); ++i) {
    *(begin + ranks[i]) = before[i];
  }
}
} // namespace rr::single_cpu