#include "bnr_data_product/label_reader/PriceDetector.hpp"

#include <vector>
#include "macros.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

bnr::data_product::label_reader::RoiImage PriceDetector::run(const cv::Mat& label_img) const {
  CHECK_MAT(label_img, CV_8U, "PriceDetector input label_img");
  const cv::Mat preprocessed_image = pre_processor_.run(label_img);
  const RoiImage roi_image_bundle = mser_doer_.run(preprocessed_image);
  const std::vector<cv::Rect> post_processed_mser_boxes = post_processor_.run(roi_image_bundle.roi_vec_);
  RoiImage final_roi_image_bundle(roi_image_bundle.image_, post_processed_mser_boxes);
  return final_roi_image_bundle;
}

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
