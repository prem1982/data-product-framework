#include "bnr_data_product/panorama/PanoramaComposer.hpp"

#include <memory>
#include <algorithm>
#include <vector>

#include "macros.hpp"
#include "utils/RectUtils.hpp"

namespace bnr {
namespace data_product {
namespace panorama {

using bnr_data_product::utils::RectUtils;

  PanoramaComposer::PanoramaComposer(const cv::Rect2f& init_size, int32_t type, float meters_per_pix,
      const cv::Scalar& default_pixel_val)  {
    CHECK_ARG(meters_per_pix > 0, "meters_per_pixel must be > 0 !");

    int32_t num_rows = std::ceil((init_size.height/meters_per_pix));
    int32_t num_cols = std::ceil((init_size.width/meters_per_pix));
    num_rows = std::max(1, num_rows);  // min size of matrix is 1x1
    num_cols = std::max(1, num_cols);

    panorama_ = std::unique_ptr<ProjectedImage>(new ProjectedImage(
        cv::UMat(num_rows, num_cols, type, default_pixel_val),
        cv::Point2f(init_size.x, init_size.y), meters_per_pix, default_pixel_val));
  }

  PanoramaComposer::PanoramaComposer(int32_t num_rows, int32_t num_cols, int32_t type, float meters_per_pixel,
      const cv::Scalar& default_pixel_val)
      : PanoramaComposer(cv::Rect2f(0.0f, 0.0f, num_cols, num_rows), type, meters_per_pixel, default_pixel_val)
  {}

  std::vector<cv::Rect2f> PanoramaComposer::getIntersections(const cv::Rect2f& region) const {
    std::vector<cv::Rect2f> intersecting_areas;
    for (const auto& inserted_area : inserted_areas_) {
      if ((region & inserted_area).area() > 0) {
        intersecting_areas.push_back(inserted_area);
      }
    }
    return intersecting_areas;
  }

  std::shared_ptr<ProjectedImage> PanoramaComposer::getIntersectPixels(const cv::Rect2f& region) const {
    std::shared_ptr<ProjectedImage> intersection;
    std::vector<cv::Rect2f> intersecting_areas = getIntersections(region);
    if (intersecting_areas.size() == 0) {
      return intersection;  // nullptr
    }

    const cv::Rect2f all_intersections = RectUtils::rectUnion(intersecting_areas);
    const cv::Rect2f intersect_rect_meters = all_intersections & region;
    const cv::UMat image_out = panorama_->getSubImg(intersect_rect_meters);
    const cv::Point2f position_out(intersect_rect_meters.x, intersect_rect_meters.y);
    intersection = std::make_shared<ProjectedImage>(image_out, position_out,
        panorama_->metersPerPixel(), panorama_->defaultPixelVal());
    return intersection;
  }

  void PanoramaComposer::insert(const ProjectedImage& projectedImage) {
    const cv::Rect2f insert_rect_meters = projectedImage.boundingRect();
    inserted_areas_.push_back(insert_rect_meters);
    panorama_->overwritePixels(projectedImage);
  }

  ProjectedImage PanoramaComposer::getFullPano() const {
    return *panorama_;
  }

}  // namespace panorama
}  // namespace data_product
}  // namespace bnr
