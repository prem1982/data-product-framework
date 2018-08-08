# logging library

load("//build:data_product.bzl", 
    "get_cpp_libs_copts",
    "get_cpp_libs_deps",
    "get_opencv_copts",
    "get_opencv_deps",
    "get_jsoncpp_copts",
    "get_jsoncpp_deps")

curr_package = {"utils":"utils"}
cpp_libs_packages = {"logging":"logging", "io":"io", "macros":"macros"}

cc_library(
  name = "utils",

  srcs = [
      "src/JsonUtils.cpp",
      "src/RectUtils.cpp"
  ],
  hdrs = [
      "include/utils/JsonUtils.hpp",
      "include/utils/ParamsReader.hpp",
      "include/utils/RectUtils.hpp",
  ],

  copts = get_cpp_libs_copts(cpp_libs_packages) + get_cpp_libs_copts(curr_package.keys()) + 
      get_jsoncpp_copts() + get_opencv_copts(),
  deps = get_cpp_libs_deps(cpp_libs_packages) + get_jsoncpp_deps() + get_opencv_deps(),

  linkstatic = 1,
  visibility = ["//visibility:public"],
)
  
