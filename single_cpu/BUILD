cc_library(
    name = "single_cpu",
    srcs = [
        "enumeration_sort.cc",
        "insertion_sort.cc",
        "merge_k_sort.cc",
        "merge_sort.cc",
        "tim_sort.cc",
    ],
    hdrs = [
        "enumeration_sort.h",
        "insertion_sort.h",
        "merge_k_sort.h",
        "merge_sort.h",
        "tim_sort.h",
    ],
    copts = [
        "-std=c++20",
        "-pthread",
        "-O3",
    ],
    visibility = ["//visibility:public"],
)
