#include "bnr_data_product/label_reader/PriceDetectorPostProcessor.hpp"

#include <vector>

#include "opencv2/objdetect.hpp"
#include "utils/RectUtils.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

using bnr_data_product::utils::RectUtils;

std::vector<cv::Rect> PriceDetectorPostProcessor::run(const std::vector<cv::Rect>& mser_boxes) const {
  std::vector<cv::Rect> detected_patches;
  for (uint32_t i = 0; i < mser_boxes.size(); i++) {
    for (uint32_t j = i + 1; j < mser_boxes.size(); j++) {
      // Variables used to check rects i and j against each other
      const int32_t yDiff = std::abs(mser_boxes[i].y - mser_boxes[j].y);
      const int32_t heightDiff = std::abs(mser_boxes[i].height - mser_boxes[j].height);
      const int32_t xDiff = std::abs(mser_boxes[i].x - mser_boxes[j].x);
      const int32_t max_dist_bound = (mser_boxes[i].x < mser_boxes[j].x) ?
          xDiff - mser_boxes[i].width : xDiff - mser_boxes[j].width;
      const cv::Rect rect_union = mser_boxes[i] | mser_boxes[j];

      // If rects i and j pass all of our checks, add their union to the detected patches
      if (heightDiff < params_.height_thresh_ && max_dist_bound <= params_.distance_thresh_ &&
          yDiff < params_.y_thresh_ && checkAreaAndAspectRatio(rect_union)) {
        detected_patches.push_back(getBufferedRescaledRect(rect_union));
      }
    }

    // If rect i on its own passes our area and aspect ratio checks, add it to the detected patches
    if (checkAreaAndAspectRatio(mser_boxes[i])) {
      detected_patches.push_back(getBufferedRescaledRect(mser_boxes[i]));
    }
  }
  // Repeat the contents of the vector twice before grouping and group
  // See https://stackoverflow.com/a/21770696 for details
  std::vector<cv::Rect> detected_patches_repeated = detected_patches;
  detected_patches_repeated.insert(detected_patches_repeated.end(), detected_patches.begin(), detected_patches.end());
  groupRectangles(detected_patches_repeated, params_.group_threshold_, params_.group_epsilon_);

  return detected_patches_repeated;
}

bool PriceDetectorPostProcessor::checkAreaAndAspectRatio(const cv::Rect& input_rect) const {
  return (RectUtils::checkArea(input_rect, params_.min_area_, params_.max_area_) &&
        RectUtils::checkAspectRatio(input_rect, params_.min_aspect_, params_.max_aspect_));
}

cv::Rect PriceDetectorPostProcessor::getBufferedRescaledRect(const cv::Rect& input_rect) const {
  const cv::Rect buffered_rect = RectUtils::addBuffer(input_rect, params_.img_buffer_);
  const cv::Rect buffered_scaled_rect = RectUtils::rescaleRect(buffered_rect, scale_factor_);

  return buffered_scaled_rect;
}

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
