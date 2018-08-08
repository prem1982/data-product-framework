#include "bnr_data_product/label_reader/PriceReaderPreProcessor.hpp"

#include <vector>

#include "opencv2/photo.hpp"

#include "io/ImageUtils.hpp"
#include "macros.hpp"


namespace bnr {
namespace data_product {
namespace label_reader {

cv::Mat PriceReaderPreProcessor::run(const cv::Mat& input_img,
    const cv::Rect& detected_price) const {
  CHECK_MAT(input_img, CV_8UC1, "PriceReaderPreProcessor input input_img");
  const cv::Mat price_crop = input_img(detected_price);
  cv::Mat denoised_price_crop;
  cv::fastNlMeansDenoising(price_crop, denoised_price_crop, params_.denoising_h_,
      params_.denoising_templateWindowSize_,
      params_.denoising_searchWindowSize_);
  return denoised_price_crop;
}

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
