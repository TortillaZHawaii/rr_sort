cc_library(
    name = "openmp_cpu",
    srcs = [
        "openmp_merge_k_sort.cc",
    ],
    hdrs = [
        "openmp_merge_k_sort.h",
    ],
    copts = [
        "-fopenmp",
        "-std=c++20",
        "-pthread",
        "-O3",
    ],
    linkopts = [
        "-lgomp",
    ],
    visibility = ["//visibility:public"],
    deps = ["//single_cpu"],
)
