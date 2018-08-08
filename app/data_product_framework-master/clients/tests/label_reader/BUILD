# label_reader services

load("//build:data_product.bzl",
    "cpp_resources_dir",
    "get_data_product_libs_copts",
    "get_data_product_libs_deps",
    "get_cpp_libs_copts",
    "get_cpp_libs_deps",
    "get_opencv_copts",
    "get_opencv_deps")

data_product_libs_packages = {"label_reader":"label_reader"}
cpp_libs_packages = {"logging":"logging", "macros":"macros", "io":"io", "utils":"utils"}

cc_binary(
  name = "label_reader_test",
  srcs = ["src/label_reader_test.cpp"],
  data = ["//" + cpp_resources_dir + ":jsons"],
  copts = get_data_product_libs_copts(data_product_libs_packages.keys()) +
      get_cpp_libs_copts(cpp_libs_packages.keys()) + get_opencv_copts(),
  deps = get_data_product_libs_deps(data_product_libs_packages) +
      get_cpp_libs_deps(cpp_libs_packages) + get_opencv_deps(),
)



