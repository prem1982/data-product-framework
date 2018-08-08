load("//build:data_product.bzl", "pylint")

SRCS = ["exceptions.py",
        "datastructs.py",
       ]

pylint(SRCS)
    
py_library(
    name = "api",

    srcs = SRCS,
    data = [":pylint.log"],

    deps = ["//python/bnr/datastructs/_internal:internal"],
    visibility = ["//visibility:public"],
)
