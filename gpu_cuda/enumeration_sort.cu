#include "enumeration_sort.cuh"
#include "utils/panic.cuh"
#include "utils/string_array.cuh"
#include <cstddef>
#include <iostream>
#include <memory>

namespace rr::gpu_cuda {
using namespace rr::gpu_cuda::utils;

__device__ int compare_strings(const char *str1, const char *str2,
                               size_t length1, size_t length2) {
  int cmp = 0;
  for (int i = 0; i < length1 && i < length2; ++i) {
    if (str1[i] < str2[i]) {
      cmp = -1;
      break;
    } else if (str1[i] > str2[i]) {
      cmp = 1;
      break;
    }
  }

  if (cmp == 0) {
    if (length1 < length2)
      cmp = -1;
    else if (length1 > length2)
      cmp = 1;
  }

  return cmp;
}

__global__ void enumeration_sort_kernel(string_array input,
                                        size_t *result_positions) {
  auto tid = threadIdx.x + blockIdx.x * blockDim.x;
  if (tid >= input.size)
    return;

  size_t length = input.lengths[tid];
  size_t offset = input.offsets[tid];

  size_t rank = 0;

  for (int i = 0; i < input.size; ++i) {
    if (i == tid)
      continue;

    size_t other_length = input.lengths[i];
    size_t other_offset = input.offsets[i];

    int cmp = compare_strings(input.data + offset, input.data + other_offset,
                              length, other_length);

    if (cmp > 0 || (cmp == 0 && tid > i)) {
      ++rank;
    }
  }

  // update result
  result_positions[tid] = rank;
}

void enumeration_sort(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end) {
  auto d_arr = to_device_string_array(begin, end);
  size_t *d_res;
  checkCudaErrors(cudaMalloc(&d_res, d_arr.size * sizeof(size_t)));
  // For some reason, lower grid count per block cannot be run on my machine on
  // bible.txt. 1024 is also max number for any CUDA device.
  //
  // https://stackoverflow.com/questions/6048907/maximum-blocks-per-gridcuda
  const uint grid_count_per_block = 1024;
  const uint block_count = d_arr.size / grid_count_per_block +
                           ((d_arr.size % grid_count_per_block) ? 1 : 0);
  enumeration_sort_kernel<<<grid_count_per_block, block_count>>>(d_arr, d_res);
  checkCudaErrors(cudaPeekAtLastError());

  auto res = std::make_unique<size_t[]>(d_arr.size);
  checkCudaErrors(cudaMemcpy(res.get(), d_res, d_arr.size * sizeof(size_t),
                             cudaMemcpyDeviceToHost));

  std::vector<std::string> sorted(d_arr.size);
  for (int i = 0; i < d_arr.size; ++i) {
    sorted[res[i]] = *(begin + i);
  }

  for (int i = 0; i < d_arr.size; ++i) {
    *(begin + i) = std::move(sorted[i]);
  }

  checkCudaErrors(cudaFree(d_res));
  free_string_array(d_arr);
}
} // namespace rr::gpu_cuda