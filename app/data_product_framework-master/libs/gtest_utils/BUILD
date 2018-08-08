# logging library

load("//build:data_product.bzl", 
    "get_cpp_libs_copts",
    "get_cpp_libs_deps",
    "get_gtest_copts",
    "get_gtest_deps",
    "get_opencv_copts",
    "get_opencv_deps")

curr_package = {"gtest_utils":"gtest_utils"}
cpp_libs_packages = {"logging":"logging", "io":"io", "macros":"macros"}

cc_library(
  name = "gtest_utils",

  srcs = [
      "src/MatUtils.cpp",
      "src/VectorUtils.cpp"
  ],
  hdrs = [
      "include/gtest_utils/MatUtils.hpp",
      "include/gtest_utils/VectorUtils.hpp"
  ],

  copts = get_cpp_libs_copts(cpp_libs_packages.keys()) + get_cpp_libs_copts(curr_package.keys()) + 
      get_opencv_copts() + get_gtest_copts(),
  deps = get_cpp_libs_deps(cpp_libs_packages) + get_opencv_deps() + get_gtest_deps(),

  linkstatic = 1,
  visibility = ["//visibility:public"],
)
  
