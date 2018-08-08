load("//build:data_product.bzl", "pylint")

SRCS = ["exceptions.py",
        "metrics_computer.py",
        "confidence_scorer.py",
       ]

pylint(SRCS)
    
py_library(
    name = "api",

    srcs = SRCS,
    data = [":pylint.log"],

    deps = ["//python/bnr/metrics/_internal:internal"],
    visibility = ["//visibility:public"],
)
