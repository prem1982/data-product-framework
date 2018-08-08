load("//build:data_product.bzl", "pylint")

SRCS = ["run.py",
        "image_chunker.py",
        "detection_deduplicator.py",
        "tensorflow_detector.py",
        "object_detector.py",
       ]

pylint(SRCS)

py_test(
    name = "test",

    srcs = SRCS,
    main = "run.py",
    data = [":pylint.log",
            "//python/bnr/object_detection/test_utils:models/valid.pb"],

    deps = ["//python/bnr/datastructs:api",
            "//python/bnr/object_detection/_internal:internal",
           ],
    visibility = ["//visibility:public"],
)
