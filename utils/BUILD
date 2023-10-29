cc_library(
    name = "utils",
    srcs = [
        "benchmark/benchmark_result.cc",
        "benchmark/sort_benchmark.cc",
        "data/reader.cc",
    ],
    hdrs = [
        "benchmark/benchmark_result.h",
        "benchmark/sort_benchmark.h",
        "data/reader.h",
    ],
    copts = [
        "-std=c++20",
        "-pthread",
        "-O3",
    ],
    visibility = ["//visibility:public"],
)
