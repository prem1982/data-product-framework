#pragma once

#include <vector>

#include "opencv2/core.hpp"
#include "bnr_data_product/label_reader/definitions.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

// Performs MSER on a label after adaptive thresholding is done
class MserDoer {
 public:
  struct Params {
    cv::Size open_kernel_size_;
    cv::Size close_kernel_size_;
    cv::Size mop_kernel_size_;
    cv::Size erode_kernel_size_;

    int32_t delta_;
    int32_t min_area_;
    int32_t max_area_;
    double max_variation_;
    double min_diversity_;

    int32_t group_threshold_;
    float group_epsilon_;

    Params(const cv::Size& open_kernel_size, const cv::Size& close_kernel_size, const cv::Size& mop_kernel_size,
                   const cv::Size erode_kernel_size, int32_t delta, int32_t min_area_mser, int32_t max_area_mser,
                   double max_variation, double min_diversity, int32_t group_threshold, float group_epsilon)
      : open_kernel_size_(open_kernel_size), close_kernel_size_(close_kernel_size),
      mop_kernel_size_(mop_kernel_size), erode_kernel_size_(erode_kernel_size), delta_(delta),
      min_area_(min_area_mser), max_area_(max_area_mser), max_variation_(max_variation),
      min_diversity_(min_diversity), group_threshold_(group_threshold), group_epsilon_(group_epsilon) {}
  };

  explicit MserDoer(const Params& params) noexcept : params_(params) {}
  bnr::data_product::label_reader::RoiImage run(const cv::Mat& preprocessed_img) const;

 private:
  Params params_;

  cv::Mat runMorphology(const cv::Size& kernel_size, const cv::Mat& input_img, int32_t operation) const;
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
