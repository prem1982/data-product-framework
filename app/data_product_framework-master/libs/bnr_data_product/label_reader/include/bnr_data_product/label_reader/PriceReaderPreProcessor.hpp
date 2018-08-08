#pragma once

#include <vector>

#include "opencv2/core.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

// Performs denoising on the regions of the image where MSER identified
// potential prices to read, before those regions are passed to OCR
class PriceReaderPreProcessor {
 public:
  struct Params {
    float denoising_h_;
    int32_t denoising_templateWindowSize_;
    int32_t denoising_searchWindowSize_;
    Params(float denoising_h, int32_t denoising_templateWindowSize,
        int32_t denoising_searchWindowSize)
      : denoising_h_(denoising_h),
      denoising_templateWindowSize_(denoising_templateWindowSize),
      denoising_searchWindowSize_(denoising_searchWindowSize) {}
  };

  explicit PriceReaderPreProcessor(const Params& params) noexcept : params_(params) {}
  cv::Mat run(const cv::Mat& input_img, const cv::Rect& detected_price) const;

 private:
  Params params_;
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr

