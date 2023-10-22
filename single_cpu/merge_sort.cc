#include "merge_sort.h"
#include <vector>

namespace rr::single_cpu {
void merge(std::vector<std::string>::iterator begin,
           std::vector<std::string>::iterator mid,
           std::vector<std::string>::iterator end) {
  auto left = begin;
  auto right = mid;
  std::vector<std::string> temp;
  while (left != mid && right != end) {
    if (*left < *right) {
      temp.push_back(*left);
      ++left;
    } else {
      temp.push_back(*right);
      ++right;
    }
  }
  while (left != mid) {
    temp.push_back(*left);
    ++left;
  }
  while (right != end) {
    temp.push_back(*right);
    ++right;
  }

  for (auto i = begin; i != end; ++i) {
    *i = temp[i - begin];
  }
}

void merge_sort(std::vector<std::string>::iterator begin,
                std::vector<std::string>::iterator end) {
  if (end - begin <= 1) {
    return;
  }
  auto mid = begin + (end - begin) / 2;
  merge_sort(begin, mid);
  merge_sort(mid, end);
  merge(begin, mid, end);
}
} // namespace rr::single_cpu