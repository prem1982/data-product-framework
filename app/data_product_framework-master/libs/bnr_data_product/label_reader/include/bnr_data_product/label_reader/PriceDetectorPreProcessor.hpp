#pragma once

#include <vector>

#include "opencv2/core.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

// Runs adaptive thresholding on the image of a label to enable better MSER for
// detecting regions with prices to read
class PriceDetectorPreProcessor {
 public:
  struct Params {
    int32_t adaptive_thresh_blocksize_;
    int32_t adaptive_thresh_mean_value_;

    Params(int32_t adaptive_thresh_blocksize, int32_t adaptive_thresh_mean_value)
        : adaptive_thresh_blocksize_(adaptive_thresh_blocksize),
        adaptive_thresh_mean_value_(adaptive_thresh_mean_value) {}
  };

  PriceDetectorPreProcessor(const Params& params, float scale_factor) noexcept
      : params_(params), scale_factor_(scale_factor) {}
  cv::Mat run(const cv::Mat& label_img) const;

 private:
  Params params_;
  float scale_factor_;
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr

