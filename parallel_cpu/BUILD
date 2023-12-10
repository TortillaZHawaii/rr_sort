cc_library(
    name = "parallel_cpu",
    srcs = [
        "parallel_merge_k_sort.cc",
        "parallel_merge_sort.cc",
        "parallel_tim_sort.cc",
    ],
    hdrs = [
        "parallel_merge_k_sort.h",
        "parallel_merge_sort.h",
        "parallel_tim_sort.h",
    ],
    copts = [
        "-std=c++20",
        "-pthread",
        "-O3",
    ],
    visibility = ["//visibility:public"],
    deps = ["//single_cpu"],
)
