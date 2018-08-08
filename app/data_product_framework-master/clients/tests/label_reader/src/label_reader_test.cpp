#include <chrono> //NOLINT
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>
#include <memory>

#include "opencv2/core.hpp"

#include "bnr_data_product/LabelReader.hpp"
#include "bnr_data_product/label_reader/definitions.hpp"
#include "io/ImageUtils.hpp"
#include "logging.hpp"
#include "macros.hpp"
#include "utils/JsonUtils.hpp"

std::vector<std::pair<std::string, std::string>> loadGroundTruth(
    const std::string& ground_truth_path);
std::string extractLabelType(const std::string& image_path);

int32_t main(int32_t argc, const char* argv[]) {
  if (argc != 2) {
    log(ERROR) << "Usage: <service_name> <ground_truth_path>" << std::endl;
    return EXIT_FAILURE;
  }

  const std::string ground_truth_path(argv[1]);
  const std::string params_path_walmart1 = "clients/resources/jsons/label_reader_params.json";
  const std::string params_path_grocery = "clients/resources/jsons/label_reader_params_grocery.json";

  // Parse ground truth json file
  std::vector<std::pair<std::string, std::string>> ground_truths = loadGroundTruth(ground_truth_path);
  int32_t num_ground_truths = ground_truths.size();
  CHECK_RUNTIME(num_ground_truths > 0, "Ground truths is empty, can not run test.");
  log(INFO) << "Read in " << ground_truths.size() << " ground truths. Starting test." << std::endl;

  // Construct the LabelReader
  std::shared_ptr<bnr::data_product::LabelReader> label_reader_walmart1 =
      std::make_shared<bnr::data_product::LabelReader>(params_path_walmart1);
  std::shared_ptr<bnr::data_product::LabelReader> label_reader_grocery =
      std::make_shared<bnr::data_product::LabelReader>(params_path_grocery);

  int32_t num_correct = 0;
  double total_runtime = 0;
  // Run the label reader on every image, check for accuracy and log runtime
  for (const auto& ground_truth : ground_truths) {
    std::string image_path = ground_truth.first;

    cv::Mat image = bnr_data_product::io::ImageUtils::loadBgrImageUint8(image_path);

    auto label_type = extractLabelType(image_path);

    std::shared_ptr<bnr::data_product::LabelReader> label_reader_to_use;
    if (label_type == "walmart1") {
      label_reader_to_use = label_reader_walmart1;
    } else if (label_type == "grocery") {
      label_reader_to_use = label_reader_grocery;
    } else {
     throw std::runtime_error("Invalid label type");
    }
    auto start = std::chrono::steady_clock::now();
    auto output = label_reader_to_use->run(image);
    auto end = std::chrono::steady_clock::now();
    total_runtime += std::chrono::duration<double, std::milli>(end - start).count();


    std::string price_read = output.symbol_;
    if (price_read == ground_truth.second) {
      num_correct++;
    }
  }

  // Compute and print accuracy
  float accuracy = static_cast<float>(num_correct) / static_cast<float>(num_ground_truths);
  log(INFO) << "Accuracy: " << accuracy << std::endl;

  // Compute and print average runtime
  float average_runtime = total_runtime / static_cast<double>(num_ground_truths);
  log(INFO) << "Average runtime: " << average_runtime << " ms" << std::endl;
  return EXIT_SUCCESS;
}

std::vector<std::pair<std::string, std::string>> loadGroundTruth(
    const std::string& ground_truth_path) {
  auto ground_truth_json = bnr_data_product::utils::JsonUtils::loadJson(ground_truth_path);
  auto path_prefix = bnr_data_product::utils::JsonUtils::getJsonValue<
      std::string>(ground_truth_json, "path_prefix");
  auto image_jsons = bnr_data_product::utils::JsonUtils::getJsonValue<
      bnr_data_product::io::Json>(ground_truth_json, "images");

  std::vector<std::pair<std::string, std::string>> ground_truths;
  for (const auto& image_json : image_jsons) {
    std::string image_path = bnr_data_product::utils::JsonUtils::getJsonValue<
        std::string>(image_json, "path");
    std::string price = bnr_data_product::utils::JsonUtils::getJsonValue<
        std::string>(image_json, "price");
    std::string final_image_path = path_prefix + image_path;
    ground_truths.emplace_back(final_image_path, price);
  }

  return ground_truths;
}

std::string extractLabelType(const std::string& image_path) {
  auto found_pos = image_path.find_last_of("/\\");
  auto image_name = image_path.substr(found_pos + 1);
  auto label_type = image_name.substr(0, image_name.find('_'));
  return label_type;
}

