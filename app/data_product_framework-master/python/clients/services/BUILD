load("@py_deps//:requirements.bzl", "requirement")
load("//build:data_product.bzl", "pylint")

SRCS = ["detect_objects.py",
        "visualize_dataset.py",
        "grade_dataset.py",
       ]

pylint(SRCS)

py_binary(
    name = "detect_objects",

    srcs = ["detect_objects.py"],
    data = [":pylint.log"],
    deps = ["//python/bnr/object_detection:api",
            requirement("Pillow"),
            requirement("scipy"),
           ],

    visibility = ["//visibility:public"],
)

py_binary(
    name = "visualize_dataset",

    srcs = ["visualize_dataset.py"],
    data = [":pylint.log"],
    deps = ["//python/bnr/datastructs:api",
            "//python/bnr/object_detection:api",
            requirement("opencv-python"),
           ],

    visibility = ["//visibility:public"],
)

py_binary(
    name = "grade_dataset",

    srcs = ["grade_dataset.py"],
    data = [":pylint.log"],
    deps = ["//python/bnr/datastructs:api",
            "//python/bnr/object_detection:api",
            "//python/bnr/metrics:api",
            requirement("Pillow"),
            requirement("scipy"),
           ],

    visibility = ["//visibility:public"],
)
