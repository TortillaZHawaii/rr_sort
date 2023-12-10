cc_binary(
    name = "main",
    srcs = ["main.cc"],
    copts = [
        "-fopenmp",
        "-std=c++20",
        "-pthread",
        "-O3",
    ],
    deps = [
        # "//gpu_cuda",
        "//openmp_cpu",
        "//parallel_cpu",
        "//single_cpu",
        "//utils",
    ],
)
