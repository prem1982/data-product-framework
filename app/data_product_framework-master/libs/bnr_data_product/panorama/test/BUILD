# bnr_data_product/panorama/gamma_correction unit tests

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
	"panorama/GammaCorrector_test.cpp",
	"panorama/PanoramaComposer_test.cpp",
	"panorama/ProjectedImage_test.cpp"
]

HEADERS = []

data_product_libs_packages = {"panorama":"panorama"}
cpp_libs_packages = {"gtest_utils":"gtest_utils"}

cc_test(
	name = "panorama_test",
	srcs = [source_prefix + source for source in SOURCES] +
			[header_prefix + header for header in HEADERS],
	copts = get_data_product_libs_copts(data_product_libs_packages.keys()) +
    		get_cpp_libs_copts(cpp_libs_packages.keys()) + get_gtest_copts(),
	deps =  get_data_product_libs_deps(data_product_libs_packages) +
      get_cpp_libs_deps(cpp_libs_packages) + get_gtest_deps()
)