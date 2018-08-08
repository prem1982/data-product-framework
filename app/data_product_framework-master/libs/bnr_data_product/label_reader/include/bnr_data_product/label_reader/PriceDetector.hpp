#pragma once

#include <vector>

#include "opencv2/core.hpp"
#include "bnr_data_product/label_reader/definitions.hpp"
#include "bnr_data_product/label_reader/MserDoer.hpp"
#include "bnr_data_product/label_reader/PriceDetectorPostProcessor.hpp"
#include "bnr_data_product/label_reader/PriceDetectorPreProcessor.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

// Given the crop of a label, detects regions where it believes there may be prices
// to read
class PriceDetector {
 public:
  struct Params {
    PriceDetectorPreProcessor::Params pre_processor_params_;
    MserDoer::Params mser_doer_params_;
    PriceDetectorPostProcessor::Params post_processor_params_;

    Params(const PriceDetectorPreProcessor::Params& pre_processor_params,
        const MserDoer::Params& mser_doer_params,
        const PriceDetectorPostProcessor::Params& post_processor_params)
        : pre_processor_params_(pre_processor_params), mser_doer_params_(mser_doer_params),
        post_processor_params_(post_processor_params) {}
  };

  PriceDetector(Params params, float scale_factor)
      : pre_processor_(params.pre_processor_params_, scale_factor),
      mser_doer_(params.mser_doer_params_), post_processor_(params.post_processor_params_, 1.0f/scale_factor) {}
  bnr::data_product::label_reader::RoiImage run(const cv::Mat& label_img) const;

 private:
  PriceDetectorPreProcessor pre_processor_;
  MserDoer mser_doer_;
  PriceDetectorPostProcessor post_processor_;
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr

