/**
 * @file definitions.hpp
 *
 * @brief Header file for common definitions across the label_reader library
 *
 * @copyright 2018 Bossa Nova Robotics. All rights reserved.
 */
#pragma once

#include <vector>

#include "opencv2/core.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

/**
 * @brief Image with regions of interest
 * 
 */
struct RoiImage {
  /** The image mat */
  cv::Mat image_;
  /** ROIs in the image */
  std::vector<cv::Rect> roi_vec_;
  /**
   * @brief construct a <code>RoiImage</code>
   *
   * @param[in] image
   * @param[in] ROIs in the image
   * 
   */
  RoiImage(const cv::Mat& image, const std::vector<cv::Rect>& roi_vec) :
    image_(image), roi_vec_(roi_vec) {}
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
