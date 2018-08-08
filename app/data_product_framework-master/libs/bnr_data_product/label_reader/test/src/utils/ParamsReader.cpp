#include "bnr_data_product/utils/ParamsReader.hpp"

#include <string>

#include "gtest/gtest.h"

using bnr_data_product::utils::ParamsReader;

static const char jsons_dir[] = "libs/bnr_data_product/label_reader/test/resources/jsons/";

TEST(ParamsReader, allValuesThere) {
  ParamsReader params_reader(std::string(jsons_dir) + "params_reader_full.json");

  const auto label_reader_params = params_reader.run<
      bnr::data_product::LabelReaderPri::Params>();
  EXPECT_FLOAT_EQ(0.1f, label_reader_params.scale_factor_);
  EXPECT_EQ(cv::Rect2f(0.7f, 0.8f, 0.9f, 1.0f), label_reader_params.nominal_patch_);
  // Test PriceDetector::Params are read correctly
  const auto price_detector_params = label_reader_params.price_detector_params_;
  // PreProcessor
  const auto price_detector_pre_processor_params = price_detector_params.pre_processor_params_;
  EXPECT_EQ(1, price_detector_pre_processor_params.adaptive_thresh_blocksize_);
  EXPECT_EQ(2, price_detector_pre_processor_params.adaptive_thresh_mean_value_);
  // MserDoer
  const auto price_detector_mser_doer_params = price_detector_params.mser_doer_params_;
  EXPECT_EQ(cv::Size(3, 4), price_detector_mser_doer_params.open_kernel_size_);
  EXPECT_EQ(cv::Size(5, 6), price_detector_mser_doer_params.close_kernel_size_);
  EXPECT_EQ(cv::Size(7, 8), price_detector_mser_doer_params.mop_kernel_size_);
  EXPECT_EQ(cv::Size(9, 10), price_detector_mser_doer_params.erode_kernel_size_);
  EXPECT_EQ(11, price_detector_mser_doer_params.delta_);
  EXPECT_EQ(12, price_detector_mser_doer_params.min_area_);
  EXPECT_EQ(13, price_detector_mser_doer_params.max_area_);
  EXPECT_DOUBLE_EQ(0.01, price_detector_mser_doer_params.max_variation_);
  EXPECT_DOUBLE_EQ(0.02, price_detector_mser_doer_params.min_diversity_);
  EXPECT_EQ(14, price_detector_mser_doer_params.group_threshold_);
  EXPECT_FLOAT_EQ(0.2, price_detector_mser_doer_params.group_epsilon_);
  // PostProcessor
  const auto price_detector_post_processor_params = price_detector_params.post_processor_params_;
  EXPECT_EQ(15, price_detector_post_processor_params.min_area_);
  EXPECT_EQ(16, price_detector_post_processor_params.max_area_);
  EXPECT_EQ(17, price_detector_post_processor_params.height_thresh_);
  EXPECT_EQ(18, price_detector_post_processor_params.distance_thresh_);
  EXPECT_EQ(19, price_detector_post_processor_params.y_thresh_);
  EXPECT_FLOAT_EQ(0.3, price_detector_post_processor_params.min_aspect_);
  EXPECT_FLOAT_EQ(0.4, price_detector_post_processor_params.max_aspect_);
  EXPECT_EQ(20, price_detector_post_processor_params.img_buffer_);
  EXPECT_EQ(21, price_detector_post_processor_params.group_threshold_);
  EXPECT_FLOAT_EQ(0.5, price_detector_post_processor_params.group_epsilon_);

  // Test PriceReader::Params are read correctly
  const auto price_reader_params = label_reader_params.price_reader_params_;
  // PreProcessor
  const auto price_reader_pre_processor_params = price_reader_params.pre_processor_params_;
  EXPECT_FLOAT_EQ(0.6, price_reader_pre_processor_params.denoising_h_);
  EXPECT_EQ(22, price_reader_pre_processor_params.denoising_templateWindowSize_);
  EXPECT_EQ(23, price_reader_pre_processor_params.denoising_searchWindowSize_);
}

