#include "bnr_data_product/label_reader/MserDoer.hpp"

#include <vector>

#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/objdetect.hpp"

#include "bnr_data_product/label_reader/definitions.hpp"
#include "macros.hpp"
#include "io/ImageUtils.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

bnr::data_product::label_reader::RoiImage MserDoer::run(const cv::Mat& preprocessed_img) const {
  CHECK_MAT(preprocessed_img, CV_8UC1, "MserDoer input preprocessed_img");


  // Run erosion/dilation morphology on the input image
  cv::Mat opened_img = runMorphology(params_.open_kernel_size_, preprocessed_img, cv::MORPH_OPEN);
  cv::Mat closed_img = runMorphology(params_.close_kernel_size_, opened_img, cv::MORPH_CLOSE);
  cv::Mat mopped_img = runMorphology(params_.mop_kernel_size_, closed_img, CV_MOP_CLOSE);
  cv::Mat eroded_img = runMorphology(params_.erode_kernel_size_, mopped_img, cv::MORPH_ERODE);

  // Detect and group regions of interest
  std::vector<std::vector<cv::Point>> mser_contours;
  std::vector<cv::Rect> mser_boxes;
  cv::Ptr<cv::MSER> mserExtractor = cv::MSER::create(params_.delta_, params_.min_area_,
      params_.max_area_, params_.max_variation_, params_.min_diversity_);
  mserExtractor->detectRegions(eroded_img, mser_contours, mser_boxes);
  groupRectangles(mser_boxes, params_.group_threshold_, params_.group_epsilon_);

  RoiImage roi_image_bundle(opened_img, mser_boxes);

  return roi_image_bundle;
}

cv::Mat MserDoer::runMorphology(const cv::Size& kernel_size, const cv::Mat& input_img,
    int32_t operation) const {
  // Create the kernel and morph the input image
  cv::Mat kernel = getStructuringElement(cv::MORPH_ELLIPSE, kernel_size);
  cv::Mat morphedImage;
  cv::morphologyEx(input_img, morphedImage, operation, kernel);

  return morphedImage;
}

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
