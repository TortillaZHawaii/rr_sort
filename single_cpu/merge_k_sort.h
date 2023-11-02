#pragma once

#include <queue>
#include <string>
#include <vector>

namespace rr::single_cpu {
std::vector<std::string> merge_k(std::vector<std::queue<std::string>>);

void merge_k_sort(std::vector<std::string>::iterator begin,
                  std::vector<std::string>::iterator end, int k);
} // namespace rr::single_cpu
