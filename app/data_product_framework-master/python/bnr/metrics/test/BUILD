load("//build:data_product.bzl", "pylint")

SRCS = ["run.py",
        "metrics_computer.py",
        "confidence_scorer.py",
       ]

pylint(SRCS)

py_test(
    name = "test",

    srcs = SRCS,
    main = "run.py",
    data = [":pylint.log"],

    deps = ["//python/bnr/datastructs:api",
            "//python/bnr/metrics/_internal:internal",
           ],
    visibility = ["//visibility:public"],
)
