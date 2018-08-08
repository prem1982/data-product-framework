# libraries

load("//build:data_product.bzl", "data_product_libs_dir")

test_suite(
  name = "bnr_data_product_test",
  tests = [
      "//" + data_product_libs_dir + "/label_reader/test:label_reader_test",
      "//" + data_product_libs_dir + "/panorama/test:panorama_test"
  ],
  visibility = ["//visibility:public"],
)

filegroup(
  name = "bnr_data_product",
  srcs = [
      "//" + data_product_libs_dir + "/label_reader:label_reader",
      "//" + data_product_libs_dir + "/panorama:panorama"
  ],
  visibility = ["//visibility:public"],
)

