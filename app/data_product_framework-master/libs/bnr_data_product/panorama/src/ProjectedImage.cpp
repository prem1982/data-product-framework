#include "bnr_data_product/panorama/ProjectedImage.hpp"

#include <iostream>

#include "macros.hpp"
#include "utils/RectUtils.hpp"

namespace bnr {
namespace data_product {
namespace panorama {

  using bnr_data_product::utils::RectUtils;

  ProjectedImage::ProjectedImage(const cv::UMat& image, const cv::Point2f& position,
      float meters_per_pix, const cv::Scalar& default_pixel_val) :
      image_(image), pos_(position), meters_per_pix_(meters_per_pix), default_pixel_val_(default_pixel_val) {
  }

  cv::Rect2f ProjectedImage::boundingRect() const {
    return cv::Rect2f(pos_.x, pos_.y, image_.cols * meters_per_pix_, image_.rows * meters_per_pix_);
  }

  cv::Rect2f ProjectedImage::findRectPixels(const cv::Rect2f& meter_rect) const {
    return RectUtils::shiftAndRescaleRect<float>(meter_rect, -1.0f*pos_.x, -1.0f*pos_.y, 1.0f/meters_per_pix_);
  }

  void ProjectedImage::overwritePixels(const ProjectedImage& new_val) {
    CHECK_ARG(FLOAT_EQ(new_val.metersPerPixel(), meters_per_pix_, .000001f),
        "Cannot overwrite ProjectedImage pixels, meters_per_pixel mismatch");
    cv::Rect2f new_val_rect_pixels = findRectPixels(new_val.boundingRect());
    CHECK_UMAT(new_val.image(), image_.type(), "new pixels in overwritePixels",
        image_.channels(), false, false, true,
        cv::Size(new_val_rect_pixels.width, new_val_rect_pixels.height));

    if (!RectUtils::checkWithinImage(new_val_rect_pixels, height(), width())) {
      // larger size = union of rects
      const cv::Rect2f orig_img_bounds = boundingRect();
      const cv::Rect2f insert_img_bounds = new_val.boundingRect();
      const cv::Rect2f enlaraged_img_bounds = orig_img_bounds | insert_img_bounds;

      // Now create a larger image and copy the old data into that image.
      cv::Point2f new_pos = cv::Point2f(enlaraged_img_bounds.x, enlaraged_img_bounds.y);
      cv::UMat new_image = cv::UMat(enlaraged_img_bounds.height/meters_per_pix_ + .001f,
          enlaraged_img_bounds.width/meters_per_pix_ +.001f,
          image_.type(), default_pixel_val_);
      ProjectedImage large_img_tmp = ProjectedImage(new_image, new_pos, meters_per_pix_, default_pixel_val_);
      large_img_tmp.overwritePixels(*this); // copy ourself into the larger buffer

      // now set ourself to the larger buffer and then add the new img
      pos_ = large_img_tmp.position();
      image_ = large_img_tmp.image();
      new_val_rect_pixels = findRectPixels(new_val.boundingRect());
    }

    new_val.image().copyTo(image_(new_val_rect_pixels));
  }

  cv::UMat ProjectedImage::getSubImg(const cv::Rect2f& meter_rect) const {
    const cv::Rect2i intersect_rect_pixels = findRectPixels(meter_rect);
    CHECK_ARG(RectUtils::checkWithinImage(intersect_rect_pixels, height(), width()), "ROI larger than image");
    return image_(intersect_rect_pixels);
  }

}  // namespace panorama
}  // namespace data_product
}  // namespace bnr
