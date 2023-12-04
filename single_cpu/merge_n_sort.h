#pragma once

#include <string>
#include <utility>
#include <vector>

namespace rr::single_cpu {
using BeginEndPair = std::pair<std::vector<std::string>::iterator,
                               std::vector<std::string>::iterator>;
// https://leetcode.com/problems/merge-k-sorted-lists/solutions/
std::vector<std::string>
merge_n(std::vector<rr::single_cpu::BeginEndPair> &ranges);

void merge_n_sort(std::vector<std::string>::iterator begin,
                  std::vector<std::string>::iterator end);

void merge_n_sort_with_n(std::vector<std::string>::iterator begin,
                         std::vector<std::string>::iterator end, int n);
} // namespace rr::single_cpu
