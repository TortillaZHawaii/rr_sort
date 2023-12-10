#pragma once

#include <string>
#include <utility>
#include <vector>

namespace rr::openmp_cpu {
void openmp_merge_k_sort(std::vector<std::string>::iterator begin,
                         std::vector<std::string>::iterator end);

void openmp_merge_k_sort_with_k(std::vector<std::string>::iterator begin,
                                std::vector<std::string>::iterator end, int k);
} // namespace rr::openmp_cpu
