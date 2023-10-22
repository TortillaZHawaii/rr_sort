cc_binary(
    name = "main",
    srcs = ["main.cc"],
    copts = [
        "-std=c++20",
        "-pthread",
        "-O3",
    ],
    deps = [
        "//parallel_cpu",
        "//single_cpu",
        "//utils",
    ],
)
