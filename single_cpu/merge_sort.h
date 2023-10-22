#pragma once

#include <string>
#include <vector>

namespace rr::single_cpu {
void merge_sort(std::vector<std::string>::iterator begin,
                std::vector<std::string>::iterator end);
} // namespace rr::single_cpu