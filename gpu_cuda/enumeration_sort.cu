#include "enumeration_sort.cuh"
#include "utils/string_array.cuh"

namespace rr::gpu_cuda {
using namespace rr::gpu_cuda::utils;

__global__ void enumeration_sort_kernel(string_array input,
                                        string_array result) {
  auto tid = threadIdx.x + blockIdx.x * blockDim.x;
  if (tid >= input.size)
    return;

  size_t length = input.lengths[tid];
  size_t offset = input.offsets[tid];

  int rank = 0;

  for (int i = 0; i < input.size; ++i) {
    if (i == tid)
      continue;

    size_t other_length = input.lengths[i];
    size_t other_offset = input.offsets[i];

    // compare strings
    int cmp = 0;
  }
}

void enumeration_sort(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
  auto d_arr = to_device_string_array(begin, end);
  auto d_res =
      create_string_array(d_arr.size, d_arr.max_length, d_arr.max_length);

  const uint grid_size = 1024;
  const uint block_size =
      d_arr.size / grid_size + (d_arr.size % grid_size) ? 1 : 0;

  enumeration_sort_kernel<<<grid_size, block_size>>>(d_arr, d_res);

  copy_string_array_to_vector(d_res, begin, end);

  free_string_array(d_arr);
  free_string_array(d_res);
}
} // namespace rr::gpu_cuda