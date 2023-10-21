load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_cuda",
    sha256 = "2f8c8c8c85f727bec4423efecec12d3b751cb0a98bda99f0f9d351608a23b858",
    strip_prefix = "rules_cuda-v0.2.1",
    urls = ["https://github.com/bazel-contrib/rules_cuda/releases/download/v0.2.1/rules_cuda-v0.2.1.tar.gz"],
)

load("@rules_cuda//cuda:repositories.bzl", "register_detected_cuda_toolchains", "rules_cuda_dependencies")

rules_cuda_dependencies()

register_detected_cuda_toolchains()
