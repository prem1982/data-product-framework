# logging library

load("//build:data_product.bzl", 
    "get_cpp_libs_copts")

curr_package = {"logging":"logging"}

filegroup(
  name = "logging_headers",
  srcs = ["include/logging.hpp"],
  visibility = ["//visibility:public"],
)

cc_library(
  name = "logging",

  srcs = ["src/logging.cpp"],
  hdrs = [":logging_headers"],

  copts = get_cpp_libs_copts(curr_package.keys()),

  linkstatic = 1,
  visibility = ["//visibility:public"],
)
  
