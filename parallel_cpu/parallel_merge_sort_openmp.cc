#include "parallel_merge_sort_openmp.h"
#include "../single_cpu/merge_sort.h"
#include <omp.h>

namespace rr::parallel_cpu {
    constexpr int kMinParallelSize = 2048;

    void parallel_merge_sort_openmp(std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end) {
        if (end - begin <= kMinParallelSize) {
            rr::single_cpu::merge_sort(begin, end);
        } else {
            auto mid = begin + (end - begin) / 2;

            #pragma omp parallel sections
            {
                #pragma omp section
                {
                    parallel_merge_sort_openmp(begin, mid);
                }

                #pragma omp section
                {
                    parallel_merge_sort_openmp(mid, end);
                }
            }

            rr::single_cpu::merge(begin, mid, end);
        }
    }
} // namespace rr::parallel_cpu