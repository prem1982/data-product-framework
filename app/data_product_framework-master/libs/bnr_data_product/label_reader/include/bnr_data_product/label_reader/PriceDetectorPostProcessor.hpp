#pragma once

#include <vector>

#include "opencv2/core.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

// Runs a series of sanity checks of the possible price locations found by MSER and
// then groups the rectangles together
class PriceDetectorPostProcessor {
 public:
  struct Params {
    int32_t min_area_;
    int32_t max_area_;
    int32_t height_thresh_;
    int32_t distance_thresh_;
    int32_t y_thresh_;
    float min_aspect_;
    float max_aspect_;

    int32_t img_buffer_;

    int32_t group_threshold_;
    float group_epsilon_;

    Params(int32_t min_area, int32_t max_area, int32_t height_thresh, int32_t distance_thresh, int32_t y_thresh,
        float min_aspect, float max_aspect, int32_t img_buffer, int32_t group_threshold, float group_epsilon)
        : min_area_(min_area), max_area_(max_area), height_thresh_(height_thresh), distance_thresh_(distance_thresh),
        y_thresh_(y_thresh), min_aspect_(min_aspect), max_aspect_(max_aspect), img_buffer_(img_buffer),
        group_threshold_(group_threshold), group_epsilon_(group_epsilon) {}
  };

  PriceDetectorPostProcessor(const Params& params, float scale_factor) noexcept
    : params_(params), scale_factor_(scale_factor) {}
  std::vector<cv::Rect> run(const std::vector<cv::Rect>& mser_boxes) const;

 private:
  Params params_;
  float scale_factor_;

  bool checkAreaAndAspectRatio(const cv::Rect& input_rect) const;
  cv::Rect getBufferedRescaledRect(const cv::Rect& input_rect) const;
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr

