load("@py_deps//:requirements.bzl", "requirement")

py_binary(
    name = "build_test_models",
    srcs = ["scripts/build_test_models.py"],
    deps = [requirement("tensorflow-gpu")],
    visibility = ["//visibility:public"],
)

genrule(
    name = "gen_test_models",
    outs = ["models/valid.pb"],
    tools = [":build_test_models"],
    cmd = "$(location :build_test_models) $(@D)",
    visibility = ["//visibility:public"],
)
