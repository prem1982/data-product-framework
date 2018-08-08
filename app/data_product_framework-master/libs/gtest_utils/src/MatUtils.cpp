#include "gtest_utils/MatUtils.hpp"

#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"
#include "opencv2/imgproc.hpp"

namespace bnr_data_product {
namespace gtest_utils {

const std::unordered_set<int32_t> MatUtils::mat_types {
    CV_8UC1, CV_8UC2, CV_8UC3, CV_8UC4,
    CV_8SC1, CV_8SC2, CV_8SC3, CV_8SC4,
    CV_16UC1, CV_16UC2, CV_16UC3, CV_16UC4,
    CV_16SC1, CV_16SC2, CV_16SC3, CV_16SC4,
    CV_32SC1, CV_32SC2, CV_32SC3, CV_32SC4,
    CV_32FC1, CV_32FC2, CV_32FC3, CV_32FC4,
    CV_64FC1, CV_64FC2, CV_64FC3, CV_64FC4
};

template<typename T>
void MatUtils::verifyMatsCheck(std::function<void(T, T)> check, const cv::Mat& mat1, const cv::Mat& mat2) {
  ASSERT_EQ(mat1.rows, mat2.rows);
  ASSERT_EQ(mat1.cols, mat2.cols);
  ASSERT_EQ(mat1.channels(), mat2.channels());
  ASSERT_EQ(mat1.type(), mat2.type());

  std::vector<cv::Mat> mat1Chans;
  split(mat1, mat1Chans);

  std::vector<cv::Mat> mat2Chans;
  split(mat2, mat2Chans);

  for (uint32_t iChan = 0; iChan < mat1Chans.size(); iChan++) {
    for (int32_t iRow = 0; iRow < mat1.rows; iRow++) {
      for (int32_t iCol = 0; iCol < mat1.cols; iCol++) {
        const T val1 = mat1Chans[iChan].at<T>(iRow, iCol);
        const T val2 = mat2Chans[iChan].at<T>(iRow, iCol);
        check(val1, val2);
      }
    }
  }
}

template<typename T>
void MatUtils::verifyMatsEQ(const cv::Mat& mat1, const cv::Mat& mat2) {
  MatUtils::verifyMatsCheck<T>(MatUtils::checkValuesEQ<T>, mat1, mat2);
}

template void MatUtils::verifyMatsEQ<uint8_t>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsEQ<float>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsEQ<double>(const cv::Mat& mat1, const cv::Mat& mat2);

template<typename T>
void MatUtils::verifyMatsGT(const cv::Mat& mat1, const cv::Mat& mat2) {
  MatUtils::verifyMatsCheck<T>(MatUtils::checkValuesGT<T>, mat1, mat2);
}

template void MatUtils::verifyMatsGT<uint8_t>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsGT<float>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsGT<double>(const cv::Mat& mat1, const cv::Mat& mat2);

template<typename T>
void MatUtils::verifyMatsGE(const cv::Mat& mat1, const cv::Mat& mat2) {
  MatUtils::verifyMatsCheck<T>(MatUtils::checkValuesGE<T>, mat1, mat2);
}

template void MatUtils::verifyMatsGE<uint8_t>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsGE<float>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsGE<double>(const cv::Mat& mat1, const cv::Mat& mat2);

template<typename T>
void MatUtils::verifyMatsLT(const cv::Mat& mat1, const cv::Mat& mat2) {
  MatUtils::verifyMatsCheck<T>(MatUtils::checkValuesLT<T>, mat1, mat2);
}

template void MatUtils::verifyMatsLT<uint8_t>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsLT<float>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsLT<double>(const cv::Mat& mat1, const cv::Mat& mat2);

template<typename T>
void MatUtils::verifyMatsLE(const cv::Mat& mat1, const cv::Mat& mat2) {
  MatUtils::verifyMatsCheck<T>(MatUtils::checkValuesLE<T>, mat1, mat2);
}

template void MatUtils::verifyMatsLE<uint8_t>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsLE<float>(const cv::Mat& mat1, const cv::Mat& mat2);
template void MatUtils::verifyMatsLE<double>(const cv::Mat& mat1, const cv::Mat& mat2);

template<typename T>
void MatUtils::checkValuesEQ(const T& val1, const T& val2) {
  EXPECT_EQ(val1, val2);
}
template<>
void MatUtils::checkValuesEQ<float>(const float& val1, const float& val2) {
  EXPECT_FLOAT_EQ(val1, val2);
}
template<>
void MatUtils::checkValuesEQ<double>(const double& val1, const double& val2) {
  EXPECT_DOUBLE_EQ(val1, val2);
}

template void MatUtils::checkValuesEQ<uint8_t>(const uint8_t& val1, const uint8_t& val2);
template void MatUtils::checkValuesEQ<float>(const float& val1, const float& val2);
template void MatUtils::checkValuesEQ<double>(const double& val1, const double& val2);

template<typename T>
void MatUtils::checkValuesGT(const T& val1, const T& val2) {
  EXPECT_GT(val1, val2);
}

template void MatUtils::checkValuesGT<uint8_t>(const uint8_t& val1, const uint8_t& val2);
template void MatUtils::checkValuesGT<float>(const float& val1, const float& val2);
template void MatUtils::checkValuesGT<double>(const double& val1, const double& val2);

template<typename T>
void MatUtils::checkValuesGE(const T& val1, const T& val2) {
  EXPECT_GE(val1, val2);
}

template void MatUtils::checkValuesGE<uint8_t>(const uint8_t& val1, const uint8_t& val2);
template void MatUtils::checkValuesGE<float>(const float& val1, const float& val2);
template void MatUtils::checkValuesGE<double>(const double& val1, const double& val2);

template<typename T>
void MatUtils::checkValuesLT(const T& val1, const T& val2) {
  EXPECT_LT(val1, val2);
}

template void MatUtils::checkValuesLT<uint8_t>(const uint8_t& val1, const uint8_t& val2);
template void MatUtils::checkValuesLT<float>(const float& val1, const float& val2);
template void MatUtils::checkValuesLT<double>(const double& val1, const double& val2);

template<typename T>
void MatUtils::checkValuesLE(const T& val1, const T& val2) {
  EXPECT_LE(val1, val2);
}

template void MatUtils::checkValuesLE<uint8_t>(const uint8_t& val1, const uint8_t& val2);
template void MatUtils::checkValuesLE<float>(const float& val1, const float& val2);
template void MatUtils::checkValuesLE<double>(const double& val1, const double& val2);


cv::Mat MatUtils::getGray2x2Uint8Mat() {
  cv::Mat gray_mat = (cv::Mat_<uint8_t>(2, 2) << 0, 51, 51, 255);
  return gray_mat;
}

cv::Mat MatUtils::getRgb2x2Uint8Mat() {
  return getRgbUint8ColorChans();
}

cv::Mat MatUtils::getBgr2x2Uint8Mat() {
  cv::Mat rgb_chans = getRgbUint8ColorChans();
  cv::Mat bgr_chans;
  cvtColor(rgb_chans, bgr_chans, CV_RGB2BGR);

  return bgr_chans;
}

cv::Mat MatUtils::getRgbUint8ColorChans() {
  cv::Mat red_chan = (cv::Mat_<uint8_t>(2, 2) << 0, 51, 51, 255);
  cv::Mat green_chan = (cv::Mat_<uint8_t>(2, 2) << 255, 51, 51, 0);
  cv::Mat blue_chan = (cv::Mat_<uint8_t>(2, 2) << 51, 0, 255, 51);

  std::vector<cv::Mat> chans{red_chan, green_chan, blue_chan};

  cv::Mat chans_merged;
  merge(chans, chans_merged);

  return chans_merged;
}

cv::Mat MatUtils::getGray2x2FloatMat() {
  cv::Mat gray_float;
  getGray2x2Uint8Mat().convertTo(gray_float, CV_32FC1, ONE_OVER_TWO_HUNDRED_FIFTY_FIVE);

  return gray_float;
}

cv::Mat MatUtils::getRgb2x2FloatMat() {
  cv::Mat rgb_float;
  getRgb2x2Uint8Mat().convertTo(rgb_float, CV_32FC3, ONE_OVER_TWO_HUNDRED_FIFTY_FIVE);

  return rgb_float;
}

cv::Mat MatUtils::getBgr2x2FloatMat() {
  cv::Mat bgr_float;
  getBgr2x2Uint8Mat().convertTo(bgr_float, CV_32FC3, ONE_OVER_TWO_HUNDRED_FIFTY_FIVE);

  return bgr_float;
}

}  // namespace gtest_utils
}  // namespace bnr_data_product
