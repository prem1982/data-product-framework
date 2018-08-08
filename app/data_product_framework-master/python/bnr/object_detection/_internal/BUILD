load("@py_deps//:requirements.bzl", "requirement")
load("//build:data_product.bzl", "pylint")

SRCS = ["exceptions.py",
        "image_chunker.py",
        "detection_deduplicator.py",
        "tensorflow_detector.py",
        "object_detector.py",
       ]

pylint(SRCS)
    
py_library(
    name = "internal",
    srcs = SRCS,
    data = [":pylint.log"],
    deps = [requirement("numpy"),
            requirement("tensorflow-gpu"),
            "//python/bnr/utils:utils",
           ],
    visibility = ["//visibility:public"],
)
