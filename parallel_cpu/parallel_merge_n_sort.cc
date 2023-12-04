#include "parallel_merge_n_sort.h"
#include "../single_cpu/intro_sort.h"
#include "../single_cpu/merge_n_sort.h"
#include <thread>
#include <vector>

void rr::parallel_cpu::parallel_merge_n_sort(
    std::vector<std::string>::iterator begin,
    std::vector<std::string>::iterator end) {
  rr::parallel_cpu::parallel_merge_n_sort_with_n(begin, end, 10);
}

void rr::parallel_cpu::parallel_merge_n_sort_with_n(
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

  // sort each part in parallel
  std::vector<std::thread> threads(n);
  for (int i = 0; i < n; ++i) {
    threads[i] = std::thread(rr::single_cpu::intro_sort, ranges[i].first,
                             ranges[i].second);
  }

  for (auto &thread : threads) {
    thread.join();
  }

  // merge
  auto result = rr::single_cpu::merge_n(ranges);

  // copy back
  for (auto i = begin; i != end; ++i) {
    *i = result[i - begin];
  }
}