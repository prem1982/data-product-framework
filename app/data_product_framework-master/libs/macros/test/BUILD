# io unit tests

load("//build:data_product.bzl", 
    "cpp_libs_dir",
    "get_cpp_libs_copts",
    "get_cpp_libs_deps",
    "get_gtest_copts",
    "get_gtest_deps",
    "get_opencv_copts",
    "get_opencv_deps")

cpp_libs_packages = {"macros":"macros", "gtest_utils":"gtest_utils"}

cc_test(
  name = "macros_test",
  srcs = ["src/macros.cpp"],
  copts = get_cpp_libs_copts(cpp_libs_packages.keys()) + get_opencv_copts() + get_gtest_copts(),
  deps = get_cpp_libs_deps(cpp_libs_packages) + get_opencv_deps() + get_gtest_deps(),
  visibility = ["//visibility:public"],
)

