load("@rules_cuda//cuda:defs.bzl", "cuda_library")

cuda_library(
    name = "gpu_cuda",
    srcs = [
        "enumeration_sort.cu",
        "utils/string_array.cu",
        "thrust_sort.cu",
    ],
    hdrs = [
        "enumeration_sort.cuh",
        "thrust_sort.cuh",
        "utils/panic.cuh",
        "utils/string_array.cuh",
    ],
    copts = [
        "-std=c++20",
        "-O3",
    ],
    visibility = ["//visibility:public"],
)
