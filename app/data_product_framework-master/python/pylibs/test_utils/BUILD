load("//build:data_product.bzl", "pylint")

SRCS = ["json_helper.py"]

pylint(SRCS)
    
py_library(
    name = "test_utils",

    srcs = SRCS,
    data = [":pylint.log"],

    visibility = ["//visibility:public"],
)
