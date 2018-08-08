# liblabel_reader library

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

load("//build:data_product.bzl",
    "cpp_libs_dir",
    "get_data_product_libs_copts",
    "get_data_product_libs_deps",
    "get_cpp_libs_copts",
    "get_cpp_libs_deps",
    "get_opencv_copts",
    "get_opencv_deps",
    "get_jsoncpp_copts",
    "get_jsoncpp_deps",
    "get_tesseract_linkopts")

cpp_libs_packages = {"logging":"logging", "io":"io", "utils":"utils", "macros":"macros"}
curr_package = {"label_reader":"label_reader"}

source_prefix = "src/"
header_prefix = "include/bnr_data_product/"

SOURCES = [
    "api/LabelReader.cpp",
    "api/LabelReaderPri.cpp",

    "label_reader/MserDoer.cpp",
    "label_reader/PriceDetector.cpp",
    "label_reader/PriceDetectorPostProcessor.cpp",
    "label_reader/PriceDetectorPreProcessor.cpp",

    "label_reader/PriceReader.cpp",
    "label_reader/PriceReaderPreProcessor.cpp",
    "label_reader/OcrDoer.cpp",
    "label_reader/PriceReaderPostProcessor.cpp",

    "utils/ParamsReader.cpp",
]

API_HEADERS = [
    "label_reader_definitions.hpp",
    "LabelReader.hpp"
]
PRIVATE_HEADERS = [
    "api/LabelReaderPri.hpp",

    "label_reader/definitions.hpp",
    "label_reader/MserDoer.hpp",
    "label_reader/PriceDetector.hpp",
    "label_reader/PriceDetectorPostProcessor.hpp",
    "label_reader/PriceDetectorPreProcessor.hpp",

    "label_reader/PriceReader.hpp",
    "label_reader/PriceReaderPreProcessor.hpp",
    "label_reader/OcrDoer.hpp",
    "label_reader/PriceReaderPostProcessor.hpp",

    "utils/ParamsReader.hpp",
]

filegroup(
  name = "api_headers",
  srcs = [header_prefix + header for header in API_HEADERS],
)

cc_library(
  name = "label_reader",
  srcs = [source_prefix + source for source in SOURCES],
  hdrs = [":api_headers"] + [header_prefix + header for header in PRIVATE_HEADERS],
  copts = get_cpp_libs_copts(cpp_libs_packages) + get_data_product_libs_copts(curr_package.keys()) + 
      get_jsoncpp_copts() + get_opencv_copts(),
  deps = get_cpp_libs_deps(cpp_libs_packages) + get_jsoncpp_deps() + get_opencv_deps(),
  linkstatic = 1,
  linkopts = get_tesseract_linkopts(),
  visibility = ["//visibility:public"],
)

cc_binary(
  name = "libbnrdp_label_reader.so",
  srcs = [
      "//" + cpp_libs_dir + "/io:io",
      "//" + cpp_libs_dir + "/logging:logging",
      "//" + cpp_libs_dir + "/utils:utils",
      ":label_reader"
  ] + get_opencv_deps() + get_jsoncpp_deps(),
  linkopts = get_tesseract_linkopts(),
  linkshared = 1,
)

# Rules for packaging up the library into the debian
pkg_tar(
  name = "label_reader_headers",
  package_dir = "/usr/include/bnr_data_product/",
  srcs = [":api_headers"],
)

pkg_tar(
  name = "label_reader_libs",
  package_dir = "/usr/lib/bnr_data_product/",
  srcs = [":libbnrdp_label_reader.so"],
)

pkg_tar(
  name = "label_reader-data",
  deps = [
      ":label_reader_headers",
      ":label_reader_libs"
  ],
  visibility = ["//visibility:public"],
)
