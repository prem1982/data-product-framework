# data_product_framework repository

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", 
    "pkg_tar", 
    "pkg_deb")

load("//build:data_product.bzl", 
  "cpp_libs_dir",
  "data_product_libs_dir",
  "cpp_clients_dir")

test_suite(
  name = "cpp_tests",
  tests = ["//" + cpp_libs_dir + ":libs_test"],
  visibility = ["//visibility:public"],
)

test_suite(
  name = "python_tests",
  tests = ["//python:bnr_test"],
  visibility = ["//visibility:public"],
)

test_suite(
  name = "data_product_tests",
  tests = [":cpp_tests", ":python_tests"],
  visibility = ["//visibility:public"],
)

filegroup(
  name = "data_product",
  srcs = ["//" + cpp_libs_dir + ":libs",
      "//" + cpp_clients_dir + ":clients"],
  visibility = ["//visibility:public"],
)

filegroup(
  name = "python_framework",
  srcs = ["//python:bnr",
          "//python:clients",
         ],
  visibility = ["//visibility:public"],
)

pkg_tar(
  name = "bnr_data_product-data",
  extension = "tar.gz",
  deps = [
      "//" + data_product_libs_dir + "/label_reader:label_reader-data",
  ],
)

pkg_deb(
  name = "bnr_data_product-debian",
  architecture = "amd64",
  built_using = "bazel (0.13.0)",
  data = ":bnr_data_product-data",
  description = "Bossa Nova's Data Product Library",
  maintainer = "Gavriel Adler, Kyle Neblett",
  package = "bnr_data_product",
  version = "0.0.3",
)

exports_files([".pylintrc"])
exports_files(["run_pylint.sh"])
