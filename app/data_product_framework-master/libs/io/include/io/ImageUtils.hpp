#pragma once

#include <string>

#include "opencv2/core.hpp"

namespace bnr_data_product {
namespace io {

class ImageUtils {
 public:
  // Saves out a CV_8UC1 grayscale cv::Mat with range [0, 255]
  static void saveGrayImageUint8(const cv::Mat& image, const std::string& output_path);
  // Saves out a CV_32FC1 grayscale cv::Mat with range [0.0f, 1.0f]
  static void saveGrayImageFloat(const cv::Mat& image, const std::string& output_path);
  // Saves out a CV_8UC3 BGR cv::Mat with range [0, 255]
  static void saveBgrImageUint8(const cv::Mat& image, const std::string& output_path);
  // Saves out a CV_32FC3 BGR cv::Mat with range [0.0f, 1.0f]
  static void saveBgrImageFloat(const cv::Mat& image, const std::string& output_path);
  // Saves out a CV_8UC3 RGB cv::Mat with range [0, 255]
  static void saveRgbImageUint8(const cv::Mat& image, const std::string& output_path);
  // Saves out a CV_32FC3 RGB cv::Mat with range [0.0f, 1.0f]
  static void saveRgbImageFloat(const cv::Mat& image, const std::string& output_path);

  // Loads an image into a CV_8UC1 grayscale cv::Mat with range [0, 255]
  static cv::Mat loadGrayImageUint8(const std::string& input_path);
  // Loads an image into a CV_32FC1 graysacle cv::Mat with range [0.0f, 1.0f]
  static cv::Mat loadGrayImageFloat(const std::string& input_path);
  // Loads an image into a CV_8UC3 BGR cv::Mat with range [0, 255]
  static cv::Mat loadBgrImageUint8(const std::string& input_path);
  // Loads an image into a CV_32FC3 BGR cv::Mat with range [0.0f, 1.0f]
  static cv::Mat loadBgrImageFloat(const std::string& input_path);
  // Loads an image into a CV_8UC3 RGB cv::Mat with range [0, 255]
  static cv::Mat loadRgbImageUint8(const std::string& input_path);
  // Loads an image into a CV_32FC3 RGB cv::Mat with range [0.0f, 1.0f]
  static cv::Mat loadRgbImageFloat(const std::string& input_path);

 private:
  static constexpr float TWO_HUNDRED_FIFTY_FIVE = 255.0f;
  static constexpr float ONE_OVER_TWO_HUNDRED_FIFTY_FIVE = 1.0f/255.0f;
};

}  // namespace io
}  // namespace bnr_data_product
