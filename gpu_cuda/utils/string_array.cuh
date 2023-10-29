#pragma once

#include <cstddef>
#include <string>
#include <vector>

// Since we can't use std::string in CUDA, we need to create a struct that
// contains the data of the string, with the begin and length of each string
// stored in separate arrays.
//
// For example vector<string> = {"abc", "def", "ghi"} would be stored as
// string_array = {
//  size = 9,
//  max_length = 3,
//  data = "abcdefghi",
//  begins = {0, 3, 6},
//  lengths = {3, 3, 3}
// }
namespace rr::gpu_cuda::utils {
struct string_array {
  size_t size;
  size_t max_length;
  size_t total_length;

  char *data;
  size_t *offsets;
  size_t *lengths;
};
string_array create_string_array(size_t size, size_t total_length,
                                 size_t max_length);

string_array to_device_string_array(std::vector<std::string>::iterator begin,
                                    std::vector<std::string>::iterator end);

void copy_string_array_to_vector(string_array &arr,
                                 std::vector<std::string>::iterator begin,
                                 std::vector<std::string>::iterator end);

void free_string_array(string_array &arr);
} // namespace rr::gpu_cuda::utils