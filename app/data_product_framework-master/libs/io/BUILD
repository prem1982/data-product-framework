# logging library

load("//build:data_product.bzl", 
    "get_cpp_libs_copts",
    "get_cpp_libs_deps",
    "get_opencv_copts",
    "get_opencv_deps",
    "get_jsoncpp_copts",
    "get_jsoncpp_deps")

cpp_libs_packages = {"macros":"macros"}
curr_package = {"io":"io"}

cc_library(
  name = "io",

  srcs = [
      "src/ImageUtils.cpp",
  ],
  hdrs = [
      "include/io/ImageUtils.hpp",
      "include/io/Json.hpp",
  ],

  copts = get_cpp_libs_copts(curr_package.keys()) + get_cpp_libs_copts(cpp_libs_packages.keys()) + 
      get_jsoncpp_copts() + get_opencv_copts(),
  deps = get_cpp_libs_deps(cpp_libs_packages) + get_jsoncpp_deps() + get_opencv_deps(),

  linkstatic = 1,
  visibility = ["//visibility:public"],
)
  
