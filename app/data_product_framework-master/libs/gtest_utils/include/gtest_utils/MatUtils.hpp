#pragma once

#include <unordered_set>

#include "opencv2/core.hpp"

namespace bnr_data_product {
namespace gtest_utils {

class MatUtils {
 public:
  static const std::unordered_set<int32_t> mat_types;

  // Verifies that two cv::Mats are identical
  template<typename T>
  static void verifyMatsEQ(const cv::Mat& mat1, const cv::Mat& mat2);
  template<typename T>
  static void verifyMatsGT(const cv::Mat& mat1, const cv::Mat& mat2);
  template<typename T>
  static void verifyMatsGE(const cv::Mat& mat1, const cv::Mat& mat2);
  template<typename T>
  static void verifyMatsLT(const cv::Mat& mat1, const cv::Mat& mat2);
  template<typename T>
  static void verifyMatsLE(const cv::Mat& mat1, const cv::Mat& mat2);


  // 0, 51, 51, 255
  static cv::Mat getGray2x2Uint8Mat();
  // R: 0, 51, 51, 255
  // G: 255, 51, 51, 0
  // B: 51, 0, 255, 51
  static cv::Mat getRgb2x2Uint8Mat();
  // Same RGB values, but cv::Mat returned is BGR
  static cv::Mat getBgr2x2Uint8Mat();
  // gray uint8 divided by 255
  static cv::Mat getGray2x2FloatMat();
  // rgb uint8 divided by 255
  static cv::Mat getRgb2x2FloatMat();
  // bgr uint8 divided by 255
  static cv::Mat getBgr2x2FloatMat();

 private:
  static constexpr float ONE_OVER_TWO_HUNDRED_FIFTY_FIVE = 1.0f/255.0f;

  static cv::Mat getRgbUint8ColorChans();
  template<typename T>
  static void verifyMatsCheck(std::function<void(T, T)> check, const cv::Mat& mat1, const cv::Mat& mat2);
  template<typename T>
  static void checkValuesEQ(const T& val1, const T& val2);
  template<typename T>
  static void checkValuesGT(const T& val1, const T& val2);
  template<typename T>
  static void checkValuesGE(const T& val1, const T& val2);
  template<typename T>
  static void checkValuesLT(const T& val1, const T& val2);
  template<typename T>
  static void checkValuesLE(const T& val1, const T& val2);
};

}  // namespace gtest_utils
}  // namespace bnr_data_product
