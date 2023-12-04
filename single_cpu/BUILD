cc_library(
    name = "single_cpu",
    srcs = [
        "insertion_sort.cc",
        "intro_sort.cc",
        "merge_n_sort.cc",
        "merge_sort.cc",
    ],
    hdrs = [
        "insertion_sort.h",
        "intro_sort.h",
        "merge_n_sort.h",
        "merge_sort.h",
    ],
    copts = [
        "-std=c++20",
        "-pthread",
        "-O3",
    ],
    visibility = ["//visibility:public"],
)
