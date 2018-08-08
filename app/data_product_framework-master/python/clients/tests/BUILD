load("@py_deps//:requirements.bzl", "requirement")
load("//build:data_product.bzl", "pylint")

SRCS = ["detect_objects.py"]

pylint(SRCS)

py_binary(
    name = "detect_objects",

    srcs = ["detect_objects.py"],
    data = [":pylint.log"],
    deps = ["//python/bnr/object_detection:api",
            requirement("Pillow"),
            requirement("scipy")],

    visibility = ["//visibility:public"],
)
