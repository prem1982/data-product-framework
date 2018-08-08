#include "bnr_data_product/label_reader/PriceDetectorPreProcessor.hpp"

#include "opencv2/imgproc.hpp"

#include "macros.hpp"
#include "io/ImageUtils.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

cv::Mat PriceDetectorPreProcessor::run(const cv::Mat& label_img) const {
  CHECK_MAT(label_img, CV_8UC1, "PriceDetectorPreProcessor input label_img");
  cv::Mat hist_img, thresholded_img, resized_img;

  cv::equalizeHist(label_img, hist_img);
  cv::adaptiveThreshold(hist_img, thresholded_img, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY_INV,
      params_.adaptive_thresh_blocksize_, params_.adaptive_thresh_mean_value_);
  cv::resize(thresholded_img, resized_img, cv::Size(), scale_factor_, scale_factor_, cv::INTER_CUBIC);
  return resized_img;
}

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
