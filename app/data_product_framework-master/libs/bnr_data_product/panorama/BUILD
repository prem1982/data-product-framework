# libpanorama library

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
    "get_eigen_copts",
    "get_eigen_deps")

source_prefix = "src/"
header_prefix = "include/bnr_data_product/"

cpp_libs_packages = {"macros":"macros", "utils":"utils"}
curr_package = {"panorama":"panorama"}

SOURCES = [
	"GammaCorrector.cpp",
	"PanoramaComposer.cpp",
	"ProjectedImage.cpp"
]

API_HEADERS = [

]

PRIVATE_HEADERS = [
	"panorama/GammaCorrector.hpp",
	"panorama/PanoramaComposer.hpp",
	"panorama/ProjectedImage.hpp"
]

filegroup(
	name = "api_headers",
	srcs = [header_prefix + header for header in API_HEADERS]
)

cc_library(
	name = "panorama",
	srcs = [source_prefix + source for source in SOURCES],
	hdrs = [":api_headers"] + [header_prefix + header for header in PRIVATE_HEADERS],
	copts = get_cpp_libs_copts(cpp_libs_packages.keys()) + get_data_product_libs_copts(curr_package.keys()) + get_opencv_copts() + get_eigen_copts(),
	deps = get_cpp_libs_deps(cpp_libs_packages) + get_opencv_deps() + get_eigen_deps(),
	linkstatic = 1,
	visibility = ["//visibility:public"]
)
