#include "bnr_data_product/label_reader/PriceDetectorPreProcessor.hpp"

#include <vector>

#include "gtest/gtest.h"
#include "opencv2/core.hpp"

#include "gtest_utils/MatUtils.hpp"

using bnr::data_product::label_reader::PriceDetectorPreProcessor;
using bnr_data_product::gtest_utils::MatUtils;

PriceDetectorPreProcessor pre_processor_ = PriceDetectorPreProcessor(PriceDetectorPreProcessor::Params(51, 30), 0.5f);
template <typename T>
cv::Mat_<T> convertVec2DToMat(const std::vector<std::vector<T>> &input_2DVec);

static const std::vector<std::vector<uint8_t>> INPUT_2DVEC{ { 0, 0, 0, 0 },
                                                            { 0, 0, 0, 0 },
                                                            { 0, 255, 255, 0 },
                                                            { 0, 0, 0, 255 } };

static const std::vector<std::vector<uint8_t>> EXPECTED_2DVEC{ { 255, 255 }, { 179, 116 } };

static const std::vector<std::vector<uint8_t>> ALL_ZEROES_VEC{ { 0, 0, 0, 0, 0, 0 },
                                                               { 0, 0, 0, 0, 0, 0 },
                                                               { 0, 0, 0, 0, 0, 0 },
                                                               { 0, 0, 0, 0, 0, 0 } };

static const std::vector<std::vector<uint8_t>> ALL_ZEROES_EXPECTED_VEC{ { 0, 0, 0 }, { 0, 0, 0 } };

static const std::vector<std::vector<uint8_t>> ALL_WHITES_VEC{ { 255, 255, 255 },
                                                               { 255, 255, 255 },
                                                               { 255, 255, 255 } };

static const std::vector<std::vector<uint8_t>> ALL_WHITES_EXPECTED_VEC{ { 0, 0 }, { 0, 0 } };

TEST(PriceDetectorPreProcessor, someImage) {
  const cv::Mat result_mat_1 = pre_processor_.run(convertVec2DToMat(INPUT_2DVEC));
  MatUtils::verifyMatsEQ<uint8_t>(convertVec2DToMat(EXPECTED_2DVEC), result_mat_1);
}

TEST(PriceDetectorPreProcessor, allZeroes) {
  const cv::Mat result_mat_2 = pre_processor_.run(convertVec2DToMat(ALL_ZEROES_VEC));
  MatUtils::verifyMatsEQ<uint8_t>(convertVec2DToMat(ALL_ZEROES_EXPECTED_VEC), result_mat_2);
}

TEST(PriceDetectorPreProcessor, allWhites) {
  const cv::Mat result_mat_3 = pre_processor_.run(convertVec2DToMat(ALL_WHITES_VEC));
  MatUtils::verifyMatsEQ<uint8_t>(convertVec2DToMat(ALL_WHITES_EXPECTED_VEC), result_mat_3);
}

template <typename T>
cv::Mat_<T> convertVec2DToMat(const std::vector< std::vector<T> > &input_2DVec) {
  int rows = static_cast<int>(input_2DVec.size());
  int cols = static_cast<int>(input_2DVec[0].size());

  const cv::Mat_<T> cv_mat(rows, cols);
  for (int i = 0; i < rows; i++) {
    cv_mat.row(i) = cv::Mat(input_2DVec[i]).t();
  }
  return cv_mat;
}

