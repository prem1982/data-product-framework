# libraries

load("//build:data_product.bzl", 
    "cpp_libs_dir",
    "data_product_libs_dir"
)

test_suite(
  name = "libs_test",
  tests = [
      "//" + cpp_libs_dir + "/io/test:io_test",
      "//" + cpp_libs_dir + "/logging/test:logging_test",
      "//" + cpp_libs_dir + "/macros/test:macros_test",
      "//" + cpp_libs_dir + "/utils/test:utils_test",
      "//" + data_product_libs_dir + ":bnr_data_product_test"
  ],
  visibility = ["//visibility:public"],
)

filegroup(
  name = "libs",
  srcs = [
      "//" + cpp_libs_dir + "/gtest_utils:gtest_utils",
      "//" + cpp_libs_dir + "/io:io",
      "//" + cpp_libs_dir + "/logging:logging",
      "//" + cpp_libs_dir + "/macros:macros",
      "//" + cpp_libs_dir + "/utils:utils",
      "//" + data_product_libs_dir + ":bnr_data_product"
  ],
  visibility = ["//visibility:public"],
)

