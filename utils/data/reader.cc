#include "reader.h"

#include <algorithm>
#include <fstream>

namespace rr::utils::data {
std::pair<std::vector<std::string>, std::vector<std::string>>
DataReader::read_data() {
  std::ifstream file(file_name);
  std::vector<std::string> data;
  std::vector<std::string> after_sort_data;
  std::string word;

  while (file >> word) {
    data.push_back(word);
    after_sort_data.push_back(word);
  }

  std::sort(after_sort_data.begin(), after_sort_data.end());
  return {data, after_sort_data};
}
} // namespace rr::utils::data