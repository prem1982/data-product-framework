#include "io/ImageUtils.hpp"

#include <string>
#include <vector>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

#include "macros.hpp"

namespace bnr_data_product {
namespace io {

void ImageUtils::saveGrayImageUint8(const cv::Mat& image, const std::string& output_path) {
  CHECK_MAT(image, CV_8UC1, "saveGrayImageUint8 input image");
  cv::imwrite(output_path, image);
}

void ImageUtils::saveGrayImageFloat(const cv::Mat& image, const std::string& output_path) {
  CHECK_MAT(image, CV_32FC1, "saveGrayImageFloat input image");
  cv::Mat uint8_image;
  image.convertTo(uint8_image, CV_8UC1, TWO_HUNDRED_FIFTY_FIVE);

  saveGrayImageUint8(uint8_image, output_path);
}

void ImageUtils::saveBgrImageUint8(const cv::Mat& image, const std::string& output_path) {
  CHECK_MAT(image, CV_8UC3, "saveBgrImageUint8 input image", 3);
  cv::imwrite(output_path, image);
}

void ImageUtils::saveBgrImageFloat(const cv::Mat& image, const std::string& output_path) {
  CHECK_MAT(image, CV_32FC3, "saveBgrImageFloat input image", 3);
  cv::Mat uint8_image;
  image.convertTo(uint8_image, CV_8UC3, TWO_HUNDRED_FIFTY_FIVE);

  saveBgrImageUint8(uint8_image, output_path);
}

void ImageUtils::saveRgbImageUint8(const cv::Mat& image, const std::string& output_path) {
  CHECK_MAT(image, CV_8UC3, "saveRgbImageUint8 input image", 3);

  cv::Mat bgr_image;
  cvtColor(image, bgr_image, CV_RGB2BGR);

  saveBgrImageUint8(bgr_image, output_path);
}

void ImageUtils::saveRgbImageFloat(const cv::Mat& image, const std::string& output_path) {
  CHECK_MAT(image, CV_32FC3, "saveRgbImageFloat input image", 3);

  cv::Mat bgr_image;
  cvtColor(image, bgr_image, CV_RGB2BGR);

  saveBgrImageFloat(bgr_image, output_path);
}

cv::Mat ImageUtils::loadGrayImageUint8(const std::string& input_path) {
  cv::Mat loaded_image = cv::imread(input_path, cv::IMREAD_GRAYSCALE);
  CHECK_RUNTIME(loaded_image.data, "Failed to load: " + input_path);

  CHECK_MAT(loaded_image, CV_8UC1, "loadGrayImageUint8 loaded_image");
  return loaded_image;
}

cv::Mat ImageUtils::loadGrayImageFloat(const std::string& input_path) {
  cv::Mat loaded_image = loadGrayImageUint8(input_path);

  cv::Mat float_image;
  loaded_image.convertTo(float_image, CV_32F, ONE_OVER_TWO_HUNDRED_FIFTY_FIVE);

  CHECK_MAT(float_image, CV_32FC1, "loadGrayImageFloat float_image");
  return float_image;
}

cv::Mat ImageUtils::loadBgrImageUint8(const std::string& input_path) {
  cv::Mat loaded_image = cv::imread(input_path, cv::IMREAD_COLOR);
  CHECK_RUNTIME(loaded_image.data, "Failed to load: " + input_path);
  CHECK_MAT(loaded_image, CV_8UC3, "loadBgrImageUint8 loaded_image", 3);

  return loaded_image;
}

cv::Mat ImageUtils::loadBgrImageFloat(const std::string& input_path) {
  cv::Mat loaded_image = loadBgrImageUint8(input_path);

  cv::Mat float_image;
  loaded_image.convertTo(float_image, CV_32F, ONE_OVER_TWO_HUNDRED_FIFTY_FIVE);

  CHECK_MAT(float_image, CV_32FC3, "loadBgrImageFloat float_image", 3);
  return float_image;
}

cv::Mat ImageUtils::loadRgbImageUint8(const std::string& input_path) {
  cv::Mat loaded_image = loadBgrImageUint8(input_path);

  cv::Mat rgb_image;
  cvtColor(loaded_image, rgb_image, CV_BGR2RGB);

  CHECK_MAT(rgb_image, CV_8UC3, "loadRgbImageUint8 rgb_image", 3);
  return rgb_image;
}

cv::Mat ImageUtils::loadRgbImageFloat(const std::string& input_path) {
  cv::Mat loaded_image = loadRgbImageUint8(input_path);

  cv::Mat float_image;
  loaded_image.convertTo(float_image, CV_32F, ONE_OVER_TWO_HUNDRED_FIFTY_FIVE);

  CHECK_MAT(float_image, CV_32FC3, "loadRgbImageFloat float_image", 3);
  return float_image;
}

}  // namespace io
}  // namespace bnr_data_product
