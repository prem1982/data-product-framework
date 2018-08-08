# clients -- tests and services

load("//build:data_product.bzl",
    "cpp_services_dir",
    "cpp_tests_dir")

filegroup(
  name = "clients",
  srcs = ["//" + cpp_services_dir + ":services",
      "//" + cpp_tests_dir + ":tests"],
  visibility = ["//visibility:public"],
)

