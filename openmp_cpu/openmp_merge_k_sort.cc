#include "openmp_merge_k_sort.h"
#include "../single_cpu/merge_k_sort.h"
#include "../single_cpu/tim_sort.h"
#include <algorithm>
#include <thread>
#include <vector>

void rr::openmp_cpu::openmp_merge_k_sort(
    std::vector<std::string>::iterator begin,
    std::vector<std::string>::iterator end) {
  rr::openmp_cpu::openmp_merge_k_sort_with_k(begin, end, 10);
}

void rr::openmp_cpu::openmp_merge_k_sort_with_k(
    std::vector<std::string>::iterator begin,
    std::vector<std::string>::iterator end, int k) {
  if (end - begin <= 1) {
    return;
  }

  // divide into n parts
  std::vector<rr::single_cpu::BeginEndPair> ranges;
  auto step = (end - begin) / k;
  auto start = begin;
  for (int i = 0; i < k; ++i) {
    auto stop = start + step;
    if (i == k - 1) {
      stop = end;
    }
    ranges.push_back({start, stop});
    start = stop;
  }

  // sort each part in parallel
#pragma omp parallel for num_threads(k)
  for (int i = 0; i < k; ++i) {
    rr::single_cpu::tim_sort(ranges[i].first, ranges[i].second);
  }

  // merge
  auto result = rr::single_cpu::merge_k(ranges);

  // copy back
#pragma omp parallel for num_threads(k)
  for (int i = 0; i < k; ++i) {
    std::copy(result.begin() + step * i,
              std::min(result.begin() + step * (i + 1), result.end()),
              begin + step * i);
  }
}