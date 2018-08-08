load("@py_deps//:requirements.bzl", "requirement")
load("//build:data_product.bzl", "pylint")

SRCS = ["generic_verification.py"]

pylint(SRCS)
    
py_library(
    name = "utils",

    srcs = SRCS,
    data = [":pylint.log"],

    deps = [requirement("numpy")],
    visibility = ["//visibility:public"],
)
