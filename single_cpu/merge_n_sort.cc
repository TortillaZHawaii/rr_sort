#include "merge_n_sort.h"
#include "intro_sort.h"

#include <queue>
#include <vector>

struct cmp {
  bool operator()(const rr::single_cpu::BeginEndPair &a,
                  const rr::single_cpu::BeginEndPair &b) {
    return *a.first > *b.first;
  }
};

std::vector<std::string>
rr::single_cpu::merge_n(std::vector<rr::single_cpu::BeginEndPair> &ranges) {
  std::priority_queue<rr::single_cpu::BeginEndPair,
                      std::vector<rr::single_cpu::BeginEndPair>, cmp>
      pq;

  for (auto &range : ranges) {
    if (range.first != range.second) {
      pq.push(range);
    }
  }

  std::vector<std::string> result;

  while (!pq.empty()) {
    auto range = pq.top();
    pq.pop();
    result.push_back(*range.first);
    ++range.first;
    if (range.first != range.second) {
      pq.push(range);
    }
  }

  return result;
}

void rr::single_cpu::merge_n_sort(std::vector<std::string>::iterator begin,
                                  std::vector<std::string>::iterator end) {
  merge_n_sort_with_n(begin, end, 16);
}

void rr::single_cpu::merge_n_sort_with_n(
    std::vector<std::string>::iterator begin,
    std::vector<std::string>::iterator end, int n) {
  if (end - begin <= 1) {
    return;
  }

  // divide into n parts
  std::vector<rr::single_cpu::BeginEndPair> ranges;
  auto step = (end - begin) / n;
  auto start = begin;
  for (int i = 0; i < n; ++i) {
    auto stop = start + step;
    if (i == n - 1) {
      stop = end;
    }
    ranges.push_back({start, stop});
    start = stop;
  }

  // sort each part
  for (auto &range : ranges) {
    // could be any other sorting algorithm
    intro_sort(range.first, range.second);
  }

  // merge
  auto result = merge_n(ranges);

  // copy back
  for (auto i = begin; i != end; ++i) {
    *i = result[i - begin];
  }
}
