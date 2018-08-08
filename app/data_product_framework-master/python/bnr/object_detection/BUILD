load("//build:data_product.bzl", "pylint")

SRCS = ["exceptions.py",
        "object_detector.py"
       ]

pylint(SRCS)
    
py_library(
    name = "api",

    srcs = SRCS,
    data = [":pylint.log"],

    deps = ["//python/bnr/datastructs:api",
            "//python/bnr/object_detection/_internal:internal"
           ],
    visibility = ["//visibility:public"],
)
