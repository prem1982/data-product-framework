#pragma once

#include <vector>
#include <memory>

#include "opencv2/core.hpp"

#include "bnr_data_product/panorama/ProjectedImage.hpp"

namespace bnr {
namespace data_product {
namespace panorama {

/**
 * @brief PanoramaComposer Class that provides ability to incrementally generate a panorama from images
 *
 *  Intended usage is to repeatedly insert images in order moving horizontally.
 */
class PanoramaComposer {
 public:
  /**
   * @brief Create a panorama image container to build a stitched panorama.
   *
   * @param[in] init_size Expected size of panorama in meters. Try to provide a close estimate along
   * the direction of growth else unecessary re-allocations and copies will be made.
   * @param[in] meters_per_pixel Meters per pixel of the panorama image, default 0.001. Must be > 0
   * @param[in] type OpenCV code for panorama matrix type.
   * @param[in] default_pixel_val Default pixel value for panorama matrix. Default is cv::Scalar(0)
   */
  PanoramaComposer(
      const cv::Rect2f& init_size,
      int32_t type,
      float meters_per_pix = 0.001f,
      const cv::Scalar& default_pixel_val = cv::Scalar(0));

  /**
   * @brief delegates to PanoramaComposer(cv::Rect(0.0, 0.0, num_cols, num_rows), ...)
   */
  PanoramaComposer(
      int32_t num_rows, int32_t num_cols,
      int32_t type,
      float meters_per_pixel = 0.001f,
      const cv::Scalar& default_pixel_val = cv::Scalar(0));

  /**
   * @brief Finds intersection between region and pano and returns overlapping pixels.
   *
   * @note If region intersects multiple previously inserted disjoint segments, these segments are merged
   * with default_value pixels in-between and the entire merged area is returned.
   *
   * @param[in] region The rectangle corresponding to the region that overlaps with pano.. Should be in meter
   * scale.
   *
   * @return projected image containing overlap, or else nullptr
   */
  std::shared_ptr<ProjectedImage> getIntersectPixels(const cv::Rect2f& region) const;

  /**
   * @brief Insert new image into panorama
   *
   * @param[in] projectedImage Image pixels and position to be inserted. Image data should be same type/resolution as in the constructor.
   */
  void insert(const ProjectedImage& projectedImage);

  /**
   * @brief Get panorama as a single ProjectedImage
   *
   * The minimum size of the panorama returned will be 1 pixel by 1 pixel
   *
   * @return ProjectedImage representing the panorama if the returned object is valid.
   */
  ProjectedImage getFullPano() const;

 private:
  std::unique_ptr<ProjectedImage> panorama_;
  std::vector<cv::Rect2f> inserted_areas_;

  // private methods
  std::vector<cv::Rect2f> getIntersections(const cv::Rect2f& region) const;
  cv::Rect2f getImageRect(const ProjectedImage& image) const;
};  // class PanoramaComposer

}  // namespace panorama
}  // namespace data_product
}  // namespace bnr
