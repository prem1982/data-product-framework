#include <cstdlib>
#include <string>

#include "opencv2/core.hpp"

#include "bnr_data_product/LabelReader.hpp"
#include "io/ImageUtils.hpp"
#include "logging.hpp"

int32_t main(int32_t argc, const char* argv[]) {
  if (argc != 2) {
    log(ERROR) << "Usage: <service_name> <image_path>" << std::endl;
    return EXIT_FAILURE;
  }

  const std::string image_path(argv[1]);
  const std::string params_path = "clients/resources/jsons/label_reader_params_grocery.json";

  cv::Mat image = bnr_data_product::io::ImageUtils::loadBgrImageUint8(image_path);
  bnr::data_product::LabelReader label_reader(params_path);
  auto result = label_reader.run(image);
  return EXIT_SUCCESS;
}
