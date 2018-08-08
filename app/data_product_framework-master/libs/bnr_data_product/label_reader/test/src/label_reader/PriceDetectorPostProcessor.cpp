#include "bnr_data_product/label_reader/PriceDetectorPostProcessor.hpp"

#include <vector>

#include "gtest/gtest.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "gtest_utils/VectorUtils.hpp"

using bnr::data_product::label_reader::PriceDetectorPostProcessor;
using bnr_data_product::gtest_utils::VectorUtils;

PriceDetectorPostProcessor post_processor_ = PriceDetectorPostProcessor(PriceDetectorPostProcessor::Params(
    5000, 23000, 10, 100, 10, 0.4f, 1.5f, 0, 1, 0.4f), 0.5f);

static const std::vector<cv::Rect> INPUT_VEC_1{ { 0, 0, 0, 0 } };
static const std::vector<cv::Rect> INPUT_VEC_2{ { 95, 57, 25, 22 } };
static const std::vector<cv::Rect> INPUT_VEC_3{ { 160, 52, 135, 71 } };
static const std::vector<cv::Rect> EXPECTED_VEC_1;
static const std::vector<cv::Rect> EXPECTED_VEC_2{ { 80, 26, 68, 36 } };

TEST(PriceDetectorPostProcessor, allZeroesVec) {
  const std::vector<cv::Rect> result_vec_1 = post_processor_.run(INPUT_VEC_1);
  VectorUtils::verifyVectorsEqual<cv::Rect>(EXPECTED_VEC_1, result_vec_1);
}

TEST(PriceDetectorPostProcessor, rejectedVec) {
  const std::vector<cv::Rect> result_vec_2 = post_processor_.run(INPUT_VEC_2);
  VectorUtils::verifyVectorsEqual<cv::Rect>(EXPECTED_VEC_1, result_vec_2);
}

TEST(PriceDetectorPostProcessor, acceptedVec) {
  const std::vector<cv::Rect> result_vec_3 = post_processor_.run(INPUT_VEC_3);
  VectorUtils::verifyVectorsEqual<cv::Rect>(EXPECTED_VEC_2, result_vec_3);
}



