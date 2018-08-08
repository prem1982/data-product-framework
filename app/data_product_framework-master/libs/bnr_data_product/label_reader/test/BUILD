# bnr_data_product unit tests

load("//build:data_product.bzl",
    "get_data_product_libs_copts",
    "get_data_product_libs_deps",
    "get_cpp_libs_copts",
    "get_cpp_libs_deps",
    "get_opencv_copts",
    "get_opencv_deps",
    "get_jsoncpp_copts",
    "get_jsoncpp_deps",
    "get_gtest_copts",
    "get_gtest_deps",
    "cpp_libs_dir",
    "data_product_libs_dir")

source_prefix = "src/"
header_prefix = "include/"

SOURCES = [
    "api/LabelReaderPri.cpp",

    "label_reader/MserDoer.cpp",
    "label_reader/PriceDetector.cpp",
    "label_reader/PriceDetectorPostProcessor.cpp",
    "label_reader/PriceDetectorPreProcessor.cpp",
    "label_reader/PriceReaderPostProcessor.cpp",
    "utils/ParamsReader.cpp",
]
HEADERS = []

data_product_libs_packages = {"label_reader":"label_reader"}
cpp_libs_packages = {"logging":"logging", "macros":"macros", "io":"io", "utils":"utils", "gtest_utils":"gtest_utils"}

cc_test(
  name = "label_reader_test",
  srcs = [source_prefix + source for source in SOURCES] +
      [header_prefix + header for header in HEADERS],

  data = [
      "//" + data_product_libs_dir + "/label_reader/test/resources:unit_test_images",
      "//" + data_product_libs_dir + "/label_reader/test/resources:test_jsons",
  ],
  copts = get_data_product_libs_copts(data_product_libs_packages.keys()) +
      get_cpp_libs_copts(cpp_libs_packages.keys()) + 
      get_jsoncpp_copts() + get_opencv_copts() + get_gtest_copts(),
  deps = get_data_product_libs_deps(data_product_libs_packages) +
      get_cpp_libs_deps(cpp_libs_packages) + 
      get_jsoncpp_deps() + get_opencv_deps() + get_gtest_deps(),
)

