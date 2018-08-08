#pragma once

#include "opencv2/core.hpp"
#include "macros.hpp"

namespace bnr_data_product {
namespace utils {

// Common utilities for operations on cv::Rects
class RectUtils {
 public:
  // Gets the aspect ratio (height/width) of a cv::Rect
  static float getAspectRatio(const cv::Rect& input_rect);
  // Adds buffer_size border around the cv::Rect, clamps to (0, 0)
  static cv::Rect addBuffer(const cv::Rect& input_rect, int32_t buffer_size);
  // Scales x, y, width, and height by a scale_factor
  template <typename T>
  static cv::Rect rescaleRect(const cv::Rect_<T>& input_rect, float scale_factor) {
    const int32_t scaled_x = static_cast<int32_t>(std::round((scale_factor * input_rect.x)));
    const int32_t scaled_y = static_cast<int32_t>(std::round((scale_factor * input_rect.y)));
    const int32_t scaled_width = static_cast<int32_t>(std::round((scale_factor * input_rect.width)));
    const int32_t scaled_height = static_cast<int32_t>(std::round((scale_factor * input_rect.height)));

    return cv::Rect(scaled_x, scaled_y, scaled_width, scaled_height);
  }

  // Shifts first then scales
  template <typename T>
  static cv::Rect_<T> shiftAndRescaleRect(const cv::Rect_<T>& input_rect, T xs, T ys, float scale_factor) {
    cv::Rect_<T> shifted = input_rect + cv::Point_<T>(xs, ys);
    return rescaleRect<T>(shifted, scale_factor);
  }
  // Return the union of a vector of rects
  template <typename T>
  static cv::Rect_<T> rectUnion(const std::vector<cv::Rect_<T>>& rects) {
    CHECK_ARG(rects.size() > 0, "Can not compute rect union of an empty list");
    cv::Rect_<T> rect_union = rects[0];
    for (const cv::Rect_<T>& rect : rects) {
      rect_union = rect_union | rect;
    }
    return rect_union;
  }

  // Checks if a cv::Rect is entirely within an image
  static bool checkWithinImage(const cv::Rect& input_rect, int32_t img_height, int32_t img_width);
  // Checks if a cv::Rect's area is between a min and max bound
  static bool checkArea(const cv::Rect& input_rect, int32_t min_area, int32_t max_area);
  // Checks if a cv::Rect's aspect ratio is between a min and max bound
  static bool checkAspectRatio(const cv::Rect& input_rect, float min_aspect_ratio, float max_aspect_ratio);
};

}  // namespace utils
}  // namespace bnr_data_product
