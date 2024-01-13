#include "../gpu_cuda/enumeration_sort.cuh"
#include "../gpu_cuda/thrust_sort.cuh"
#include "../openmp_cpu/openmp_merge_k_sort.h"
#include "../single_cpu/merge_k_sort.h"
#include "../single_cpu/merge_sort.h"
#include "../single_cpu/tim_sort.h"
#include "../utils/data/reader.h"
#include "benchmark/benchmark.h"
#include <algorithm>

/*
Run this benchmark with the following command:
And change the path to your own path.
bazel run -c opt //gbenchmark
*/

static std::string file_name = "/home/tortilla/rr_sort/test_data/bible.txt";

static void OpenMP_MergeKSort(benchmark::State &state) {
  rr::utils::data::DataReader reader(file_name);
  auto [unsorted, sorted] = reader.read_data();
  int k = state.range(0);

  for (auto _ : state) {
    rr::openmp_cpu::openmp_merge_k_sort_with_k(unsorted.begin(), unsorted.end(),
                                               k);
  }
}

static void MergeKSort(benchmark::State &state) {
  rr::utils::data::DataReader reader(file_name);
  auto [unsorted, sorted] = reader.read_data();

  for (auto _ : state) {
    rr::single_cpu::merge_k_sort(unsorted.begin(), unsorted.end());
  }
}

static void StdSort(benchmark::State &state) {
  rr::utils::data::DataReader reader(file_name);
  auto [unsorted, sorted] = reader.read_data();

  for (auto _ : state) {
    std::sort(unsorted.begin(), unsorted.end());
  }
}

static void TimSort(benchmark::State &state) {
  rr::utils::data::DataReader reader(file_name);
  auto [unsorted, sorted] = reader.read_data();

  for (auto _ : state) {
    rr::single_cpu::tim_sort(unsorted.begin(), unsorted.end());
  }
}

static void MergeSort(benchmark::State &state) {
  rr::utils::data::DataReader reader(file_name);
  auto [unsorted, sorted] = reader.read_data();

  for (auto _ : state) {
    rr::single_cpu::merge_sort(unsorted.begin(), unsorted.end());
  }
}

static void GpuEnumSort(benchmark::State &state) {
  rr::utils::data::DataReader reader(file_name);
  auto [unsorted, sorted] = reader.read_data();

  for (auto _ : state) {
    rr::gpu_cuda::enumeration_sort(unsorted.begin(), unsorted.end());
  }
}

static void GpuThrustSort4(benchmark::State &state) {
  rr::utils::data::DataReader reader(file_name);
  auto [unsorted, sorted] = reader.read_data();

  for (auto _ : state) {
    rr::gpu_cuda::thrust_sort4(unsorted.begin(), unsorted.end());
  }
}

static void GpuThrustSort8(benchmark::State &state) {
  rr::utils::data::DataReader reader(file_name);
  auto [unsorted, sorted] = reader.read_data();

  for (auto _ : state) {
    rr::gpu_cuda::thrust_sort8(unsorted.begin(), unsorted.end());
  }
}

BENCHMARK(GpuThrustSort4);
BENCHMARK(StdSort);
BENCHMARK(GpuThrustSort8);

BENCHMARK_MAIN();
