filegroup(
    name = "clients",
    srcs = ["//python/clients:tests",
            "//python/clients:services",
           ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "bnr",
    srcs = ["//python/bnr:datastructs",
            "//python/bnr:object_detection",
            "//python/bnr:metrics",
           ],
    visibility = ["//visibility:public"],
)

test_suite(
    name = "bnr_test",
    tests = ["//python/bnr:datastructs_test",
             "//python/bnr:object_detection_test",
             "//python/bnr:metrics_test",
            ],
    visibility = ["//visibility:public"],
)

exports_files(["requirements/bazel.txt"])
