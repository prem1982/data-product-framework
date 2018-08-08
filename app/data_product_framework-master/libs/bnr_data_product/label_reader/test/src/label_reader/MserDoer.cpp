#include "bnr_data_product/label_reader/MserDoer.hpp"

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

#include "gtest_utils/VectorUtils.hpp"
#include "io/ImageUtils.hpp"

using bnr::data_product::label_reader::MserDoer;
using bnr_data_product::gtest_utils::VectorUtils;
using bnr_data_product::io::ImageUtils;

MserDoer mser_doer_ = MserDoer(MserDoer::Params(cv::Size(7, 7), cv::Size(5, 5),
      cv::Size(20, 5), cv::Size(5, 7), 5, 250, 1250, 0.25f, 0.1f, 1, 0.4f));

static const char images_dir[] = "libs/bnr_data_product/label_reader/test/resources/images/";

static const std::vector<cv::Rect> EXPECTED_VEC_1{ { 95, 57, 25, 22 } };
static const std::vector<cv::Rect> EXPECTED_VEC_2;
static const std::vector<cv::Rect> EXPECTED_VEC_3{ { 104, 37, 37, 31 }, { 154, 80, 27, 58 } };

TEST(MserDoer, withAlphabetsInImage) {
  cv::Mat input_image;
  input_image = ImageUtils::loadGrayImageUint8(std::string(images_dir) + "ab_thresh.png");
  bnr::data_product::label_reader::RoiImage roi_image_bundle = mser_doer_.run(input_image);
  VectorUtils::verifyVectorsEqual<cv::Rect>(EXPECTED_VEC_1, roi_image_bundle.roi_vec_);
}

TEST(MserDoer, withoutTextImage) {
  cv::Mat input_image;
  input_image = ImageUtils::loadGrayImageUint8(std::string(images_dir) + "fl_thresh.png");
  bnr::data_product::label_reader::RoiImage roi_image_bundle = mser_doer_.run(input_image);
  VectorUtils::verifyVectorsEqual<cv::Rect>(EXPECTED_VEC_2, roi_image_bundle.roi_vec_);
}

TEST(MserDoer, withSentenceInImage) {
  cv::Mat input_image;
  input_image = ImageUtils::loadGrayImageUint8(std::string(images_dir) + "kf_thresh.png");
  bnr::data_product::label_reader::RoiImage roi_image_bundle = mser_doer_.run(input_image);
  VectorUtils::verifyVectorsEqual<cv::Rect>(EXPECTED_VEC_3, roi_image_bundle.roi_vec_);
}

