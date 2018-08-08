#pragma once

#include "opencv2/core.hpp"

namespace bnr {
namespace data_product {
namespace panorama {

class ProjectedImage {
 public:
  /**
   * @brief Create a projectedImage which contains the an image projected at a specific location in the aisle
   *
   * @param[in] image UMat containing image pixels.
   * @param[in] position X-Y coordinates of top left corner of image in projected aisle meter coordinates
   * @param[in] meters_per_pix Resolution of the image.
   * @param[in] default_pixel_val To use when enlarging image.
   */
  ProjectedImage(const cv::UMat& image, const cv::Point2f& position,
      float meters_per_pix, const cv::Scalar& default_pixel_val);

  /*
   * @brief Copy pixels from source into ProjectedImage within the region of interest
   *
   * @param[in] source The pixel data and location to copy pixels from. Should be same type/resolution of UMat as object holds
   */
  void overwritePixels(const ProjectedImage& source);

  /*
   * @brief return subimage of projected image corresponding to the pixels covered by the roi
   *
   * @param[in] roi rectangle corresponding to pixel extent of subimage to return.
   * @return UMat corresponding to sub image
   */
  cv::UMat getSubImg(const cv::Rect2f& meter_rect) const;

  /*
   * @brief Returns bounding rect of projected image in meter coordinates.
   */
  cv::Rect2f boundingRect() const;

  /*
   * @brief Converts rectangle in meter coordinates to pixel selecting rect.
   *
   * @param[in] meter_rect Rect with x,y,width,height in meters
   *
   * @return Rect with start_col,start_row,num_cols,num_height usable to index UMat
   */
  cv::Rect2f findRectPixels(const cv::Rect2f& meter_rect) const;

  // getters
  cv::UMat image() const { return image_;}
  cv::Point2f position() const { return pos_; }
  float x() const { return pos_.x; }
  float y() const { return pos_.y; }
  int32_t width() const { return image_.cols; }
  int32_t height() const { return image_.rows; }
  float metersPerPixel() const { return meters_per_pix_; }
  cv::Scalar defaultPixelVal() const { return default_pixel_val_; }

 private:
  cv::UMat image_;
  cv::Point2f pos_;
  float meters_per_pix_;
  cv::Scalar default_pixel_val_;
};  // class ProjectedImage

}  // namespace panorama
}  // namespace data_product
}  // namespace bnr
