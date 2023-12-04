#pragma once

#include <string>
#include <utility>
#include <vector>

namespace rr::parallel_cpu {
void parallel_merge_n_sort(std::vector<std::string>::iterator begin,
                           std::vector<std::string>::iterator end);

void parallel_merge_n_sort_with_n(std::vector<std::string>::iterator begin,
                                  std::vector<std::string>::iterator end,
                                  int n);
} // namespace rr::parallel_cpu
