load("@py_deps//:requirements.bzl", "requirement")
load("//build:data_product.bzl", "pylint")

SRCS = ["exceptions.py",
        "rect.py",
        "scored_rect.py"
       ]

pylint(SRCS)
    
py_library(
    name = "internal",
    srcs = SRCS,
    data = [":pylint.log"],
    deps = ["//python/bnr/utils:utils"],
    visibility = ["//visibility:public"],
)
