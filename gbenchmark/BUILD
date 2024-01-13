load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "gbenchmark",
    srcs = ["gbenchmark.cc"],
    copts = [
        "-Iexternal/benchmark/include", 
        "-fopenmp",
        "-std=c++20",
        "-pthread",
        "-O3",
    ],
    deps = [
        "//gpu_cuda",
        "//openmp_cpu",
        "//parallel_cpu",
        "//single_cpu",
        "//utils",
        "@benchmark//:benchmark_main",
    ],
)
