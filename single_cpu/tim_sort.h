#pragma once

#include <string>
#include <vector>

namespace rr::single_cpu {
// Hybrid sort that uses insertion sort for small arrays and merge sort for
// large arrays.
void tim_sort(std::vector<std::string>::iterator begin,
              std::vector<std::string>::iterator end);
} // namespace rr::single_cpu