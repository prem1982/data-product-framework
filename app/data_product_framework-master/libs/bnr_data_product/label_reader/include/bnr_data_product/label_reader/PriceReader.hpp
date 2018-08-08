#pragma once

#include <vector>

#include "opencv2/core.hpp"

#include "bnr_data_product/label_reader/OcrDoer.hpp"
#include "bnr_data_product/label_reader/PriceReaderPreProcessor.hpp"
#include "bnr_data_product/label_reader/PriceReaderPostProcessor.hpp"
#include "bnr_data_product/label_reader_definitions.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

// Uses OCR to read prices off a label after regions that may contain
// prices have been identified by MSER
class PriceReader {
 public:
  struct Params {
    PriceReaderPreProcessor::Params pre_processor_params_;

    explicit Params(const PriceReaderPreProcessor::Params& pre_processor_params)
        : pre_processor_params_(pre_processor_params) {}
  };

  PriceReader(const Params& params, float scale_factor) noexcept
      : scale_factor_(scale_factor), pre_processor_(params.pre_processor_params_) {}
  std::vector<bnr::data_product::ReadSymbol> run(const cv::Mat& label_img,
      const std::vector<cv::Rect>& detected_prices) const;

 private:
  static constexpr int32_t MAX_NUM_ITERATIONS = 2;
  static constexpr int32_t WIDEN_WIDTH = 60;

  float scale_factor_;
  PriceReaderPreProcessor pre_processor_;
  OcrDoer ocr_doer_;
  PriceReaderPostProcessor post_processor_;

  std::vector<bnr::data_product::ReadSymbol> runAllIterations(const cv::Mat& label_img,
      const std::vector<cv::Rect>& rescaled_prices, int32_t num_iters = 1) const;
  std::vector<bnr::data_product::ReadSymbol> runSingleIteration(const cv::Mat& label_img,
      const std::vector<cv::Rect>& detected_prices) const;
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr

