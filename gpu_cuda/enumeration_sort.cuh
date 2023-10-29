#pragma once

#include <string>
#include <vector>

namespace rr::gpu_cuda {
void enumeration_sort(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end);
}