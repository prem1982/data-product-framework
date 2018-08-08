load("//build:data_product.bzl", "pylint")

SRCS = ["run.py",
        "rect.py",
        "scored_rect.py",
       ]

pylint(SRCS)

py_test(
    name = "test",

    srcs = SRCS,
    main = "run.py",
    data = [":pylint.log"],

    deps = ["//python/bnr/datastructs/_internal:internal"],
    visibility = ["//visibility:public"],
)
