#pragma once

#include <string>
#include <utility>
#include <vector>
namespace rr::utils::data {
class DataReader {
  std::string file_name;

public:
  DataReader(std::string file_name) : file_name(file_name) {}
  std::pair<std::vector<std::string>, std::vector<std::string>> read_data();
};
} // namespace rr::utils::data