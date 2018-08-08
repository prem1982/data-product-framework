# resources for label_reader unit tests
load("@py_deps//:requirements.bzl", "requirement")
load("//build:data_product.bzl", "data_product_libs_dir")
load("//build:data_product.bzl", "pylint")

SRCS = ["scripts/generate_test_jsons.py"]

pylint(SRCS)

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
      "jsons/params_reader_full.json",
  ],
  tools = [":generate_test_jsons"],
  cmd = "$(location :generate_test_jsons) $(@D)/",
  visibility = ["//visibility:public"],
  local = 1,
)

filegroup(
  name = "unit_test_images",
  srcs = [
      "images/fl_thresh.png",
      "images/ab_thresh.png",
      "images/kf_thresh.png"
  ],
  visibility = ["//visibility:public"],
)

