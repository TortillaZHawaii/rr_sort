#include "merge_k_sort.h"
#include <queue>

namespace rr::single_cpu {
bool cmp(std::queue<std::string> a, std::queue<std::string> b) {
  return a.front() >= b.front();
}

std::vector<std::string> merge_k(std::vector<std::queue<std::string>> lists) {
  std::vector<std::string> result;

  std::priority_queue<std::queue<std::string>,
                      std::vector<std::queue<std::string>>, decltype(&cmp)>
      pq(lists.begin(), lists.end(), cmp);

  while (!pq.empty()) {
    std::queue<std::string> q = pq.top();
    pq.pop();
    result.push_back(q.front());
    q.pop();
    if (!q.empty()) {
      pq.push(q);
    }
  }

  return result;
}

void merge_k_sort(std::vector<std::string>::iterator begin,
                  std::vector<std::string>::iterator end, int k) {
  std::vector<std::queue<std::string>> lists;
}
} // namespace rr::single_cpu