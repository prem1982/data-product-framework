#include "bnr_data_product/api/LabelReaderPri.hpp"

#include <vector>
#include <limits>
#include <string>

#include "opencv2/imgproc.hpp"

#include "io/ImageUtils.hpp"
#include "macros.hpp"

#include "bnr_data_product/label_reader/definitions.hpp"

namespace bnr {
namespace data_product {

bnr::data_product::ReadSymbol LabelReaderPri::run(
    const cv::Mat& label_img) const {

  CHECK_MAT(label_img, CV_8UC3, "LabelReaderPri input label_img", 3);

  // Convert input from 3 channel to gray
  cv::Mat gray_img;
  cv::cvtColor(label_img, gray_img, cv::COLOR_BGR2GRAY);

  // Detect and read prices
  const bnr::data_product::label_reader::RoiImage roi_image_bundle = price_detector_.run(gray_img);
  const std::vector<bnr::data_product::ReadSymbol> read_prices =
      price_reader_.run(roi_image_bundle.image_, roi_image_bundle.roi_vec_);

  const bnr::data_product::ReadSymbol final_symbol =
      postProcessMultiplePatches(label_img, roi_image_bundle, read_prices);

  return final_symbol;
}

// Post processing for pruning final price value in case of multiple price patch detections
// by calculating nearest patch to nominal patch
bnr::data_product::ReadSymbol LabelReaderPri::postProcessMultiplePatches(
    const cv::Mat& label_img, const bnr::data_product::label_reader::RoiImage& roi_image_bundle,
    const std::vector<bnr::data_product::ReadSymbol>& read_prices) const {

  std::string final_price_value;
  cv::Rect roi_rect;

  // 0 prices read --> return an empty price value
  if (roi_image_bundle.roi_vec_.size() == 0 || read_prices.empty()) {
    final_price_value = "";
    roi_rect = cv::Rect(0, 0, 0, 0);
  // 1 price read --> return the price
  } else if (roi_image_bundle.roi_vec_.size() == 1) {
    final_price_value = read_prices[0].symbol_;
    roi_rect = roi_image_bundle.roi_vec_[0];
  // > 1 prices read --> need to combine
  } else {
    int32_t dist_from_nominal = std::numeric_limits<int>::max();
    cv::Rect nominal_roi =
        cv::Rect(params_.nominal_patch_.x * label_img.cols, params_.nominal_patch_.y * label_img.rows,
                 params_.nominal_patch_.width * label_img.cols, params_.nominal_patch_.height * label_img.rows);
    cv::Point nominal_roi_center =
        cv::Point(nominal_roi.x + (nominal_roi.width / 2), nominal_roi.y + (nominal_roi.height / 2));

    for (uint32_t counter = 0; counter < read_prices.size(); counter++) {
      cv::Point detection_center =
          cv::Point(roi_image_bundle.roi_vec_[counter].x + (roi_image_bundle.roi_vec_[counter].width / 2),
                    roi_image_bundle.roi_vec_[counter].y + (roi_image_bundle.roi_vec_[counter].height / 2));
      double curr_dist_from_nominal = std::abs(norm(detection_center - nominal_roi_center));
      if (curr_dist_from_nominal < dist_from_nominal) {
        final_price_value = read_prices[counter].symbol_;
        roi_rect = roi_image_bundle.roi_vec_[counter];
        dist_from_nominal = curr_dist_from_nominal;
      }
    }
  }

  ReadSymbol final_text_roi_bundle(final_price_value, roi_rect, 1.0f);
  return final_text_roi_bundle;
}


}  // namespace data_product
}  // namespace bnr

