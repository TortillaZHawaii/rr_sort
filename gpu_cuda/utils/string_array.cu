#include "panic.cuh"
#include "string_array.cuh"
#include <cstddef>
#include <iostream>
#include <memory>
#include <tuple>

namespace rr::gpu_cuda::utils {
string_array create_string_array(size_t size, size_t total_length,
                                 size_t max_length) {
  string_array arr;
  arr.size = size;
  arr.total_length = total_length;
  arr.max_length = max_length;
  checkCudaErrors(cudaMalloc(&arr.data, total_length * sizeof(char)));
  checkCudaErrors(cudaMalloc(&arr.lengths, size * sizeof(size_t)));
  checkCudaErrors(cudaMalloc(&arr.offsets, size * sizeof(size_t)));
  return arr;
}

string_array to_device_string_array(std::vector<std::string>::iterator begin,
                                    std::vector<std::string>::iterator end) {
  size_t size = std::distance(begin, end);

  std::vector<int> lengths(size);
  std::vector<int> offsets(size);
  size_t max_length = 0;
  size_t total_length = 0;

  for (auto it = begin; it != end; ++it) {
    size_t length = it->length();
    if (length > max_length) {
      max_length = length;
    }
    lengths[it - begin] = length;
    offsets[it - begin] = total_length;
    total_length += length;
  }

  auto data = std::make_unique<char[]>(total_length);
  for (auto it = begin; it != end; ++it) {
    std::copy(it->begin(), it->end(), data.get() + offsets[it - begin]);
  }

  auto d_arr = create_string_array(size, total_length, max_length);
  checkCudaErrors(cudaMemcpy(d_arr.lengths, lengths.data(),
                             size * sizeof(size_t), cudaMemcpyHostToDevice));
  checkCudaErrors(cudaMemcpy(d_arr.offsets, offsets.data(),
                             size * sizeof(size_t), cudaMemcpyHostToDevice));
  checkCudaErrors(cudaMemcpy(d_arr.data, data.get(),
                             total_length * sizeof(char),
                             cudaMemcpyHostToDevice));
  return d_arr;
}

void copy_string_array_to_vector(string_array &arr,
                                 std::vector<std::string>::iterator begin,
                                 std::vector<std::string>::iterator end) {}

void free_string_array(string_array &arr) {
  checkCudaErrors(cudaFree(arr.data));
  checkCudaErrors(cudaFree(arr.lengths));
  checkCudaErrors(cudaFree(arr.offsets));
};
} // namespace rr::gpu_cuda::utils