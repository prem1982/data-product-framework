load("@py_deps//:requirements.bzl", "requirement")
load("//build:data_product.bzl", "pylint")

SRCS = ["exceptions.py",
        "metrics_computer.py",
        "confidence_scorer.py",
       ]

pylint(SRCS)
    
py_library(
    name = "internal",
    srcs = SRCS,
    data = [":pylint.log"],
    deps = ["//python/bnr/utils:utils"],
    visibility = ["//visibility:public"],
)
