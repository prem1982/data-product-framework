#include "utils/RectUtils.hpp"

#include <algorithm>

namespace bnr_data_product {
namespace utils {

float RectUtils::getAspectRatio(const cv::Rect& input_rect) {
  CHECK_ARG(input_rect.width > 0, "Can not compute aspect ratio of cv::Rect with 0 width.");
  const float aspect_ratio = static_cast<float>(input_rect.height) / static_cast<float>(input_rect.width);
  return aspect_ratio;
}

cv::Rect RectUtils::addBuffer(const cv::Rect& input_rect, int32_t buffer_size) {
  cv::Rect buffered_rect = input_rect + cv::Size(2*buffer_size, 2*buffer_size);
  buffered_rect.x = std::max(input_rect.x - buffer_size, 0);
  buffered_rect.y = std::max(input_rect.y - buffer_size, 0);

  return buffered_rect;
}

bool RectUtils::checkWithinImage(const cv::Rect& input_rect, int32_t img_height, int32_t img_width) {
  return (input_rect.br().x <= img_width && input_rect.br().y <= img_height
      && input_rect.tl().x >= 0 && input_rect.tl().y >= 0);
}

bool RectUtils::checkArea(const cv::Rect& input_rect, int32_t min_area, int32_t max_area) {
  return (input_rect.area() > min_area && input_rect.area() < max_area);
}

bool RectUtils::checkAspectRatio(const cv::Rect& input_rect, float min_aspect_ratio, float max_aspect_ratio) {
  const float aspect_ratio = getAspectRatio(input_rect);
  return (aspect_ratio < max_aspect_ratio && aspect_ratio >= min_aspect_ratio);
}

}  // namespace utils
}  // namespace bnr_data_product
