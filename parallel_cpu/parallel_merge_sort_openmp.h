#pragma once

#include <string>
#include <vector>

namespace rr::parallel_cpu {
void parallel_merge_sort_openmp(std::vector<std::string>::iterator begin,
                                std::vector<std::string>::iterator end);
} // namespace rr::parallel_cpu
