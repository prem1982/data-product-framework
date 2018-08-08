# resources for gtest_utils
load("@py_deps//:requirements.bzl", "requirement")
load("//build:data_product.bzl", "cpp_libs_dir")
load("//build:data_product.bzl", "pylint")

SRCS = ["scripts/generate_test_mats.py",
        "scripts/generate_test_jsons.py",
       ]

pylint(SRCS)

py_binary(
    name = "generate_test_mats",
    srcs = ["scripts/generate_test_mats.py"],
    data = [":pylint.log"],
    deps = [requirement("numpy"),
            requirement("Pillow"),
           ],
    visibility = ["//visibility:public"],
)

genrule(
  name = "test_mats",
  outs = [
      "images/gray_2x2_uint8.png",
      "images/rgb_2x2_uint8.png",
  ],
  tools = [":generate_test_mats"],
  cmd = "$(location :generate_test_mats) $(@D)/images/",
  visibility = ["//visibility:public"],
)

py_binary(
    name = "generate_test_jsons",
    srcs = ["scripts/generate_test_jsons.py"],
    data = [":pylint.log"],
    deps = ["//python/pylibs/test_utils:test_utils"],
    visibility = ["//visibility:public"],
)

genrule(
  name = "test_jsons",
  outs = [
      "jsons/valid_simple.json",
      "jsons/invalid_size_1.json",
      "jsons/invalid_size_2.json",
  ],
  tools = [":generate_test_jsons"],
  cmd = "$(location :generate_test_jsons) $(@D)/jsons/",
  visibility = ["//visibility:public"],
  local = 1,
)
