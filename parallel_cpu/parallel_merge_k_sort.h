#pragma once

#include <string>
#include <utility>
#include <vector>

namespace rr::parallel_cpu {
void parallel_merge_k_sort(std::vector<std::string>::iterator begin,
                           std::vector<std::string>::iterator end);

void parallel_merge_k_sort_with_k(std::vector<std::string>::iterator begin,
                                  std::vector<std::string>::iterator end,
                                  int k);
} // namespace rr::parallel_cpu
