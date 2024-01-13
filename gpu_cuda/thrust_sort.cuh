#pragma once

#include <string>
#include <vector>


namespace rr::gpu_cuda {
// Using thrust to sort the strings with 4 byte strings on GPU, the rest on CPU
void thrust_sort4(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end);
// Using thrust to sort the strings with 8 byte strings on GPU, the rest on CPU
void thrust_sort8(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end);
// same as above, but runs on two CPU threads
void thrust_sort8split(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end);
}
