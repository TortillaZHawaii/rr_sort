#include "enumeration_sort.cuh"
#include "utils/string_array.cuh"

namespace rr::gpu_cuda {
void enumeration_sort(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
  auto d_arr = rr::gpu_cuda::utils::to_device_string_array(begin, end);

  rr::gpu_cuda::utils::free_string_array(d_arr);
}
} // namespace rr::gpu_cuda