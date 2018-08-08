# logging unit tests

load("//build:data_product.bzl", 
        "get_cpp_libs_copts",
        "get_cpp_libs_deps",
        "get_gtest_copts",
        "get_gtest_deps")

cpp_libs_packages = {"logging":"logging"}

cc_test(
    name = "logging_test",

    srcs = ["src/logging.cpp"],

    copts = get_cpp_libs_copts(cpp_libs_packages.keys()) + get_gtest_copts(),
    deps = get_cpp_libs_deps(cpp_libs_packages) + get_gtest_deps(),
    visibility = ["//visibility:public"],
)

