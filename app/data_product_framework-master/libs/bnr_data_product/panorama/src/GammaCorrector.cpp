#include "bnr_data_product/panorama/GammaCorrector.hpp"

#include <cmath>

#include "macros.hpp"

namespace bnr {
namespace data_product {
namespace panorama {

GammaCorrector::GammaCorrector(double gamma) : gamma_lookup_(gamma_input_range_, 1, CV_8UC1) {
  CHECK_ARG(gamma > 0, "gamma correction factor must be positive!");
  double inverse_gamma_factor = 1.0 / gamma;
  for (int32_t input = 0; input < gamma_input_range_; input++) {
    // f(input) = G * (input/G)^(1/gamma_factor), where G is the maximum input gamma value
    double normalized_input = static_cast<double>(input) / max_gamma_input_value_;
    double gamma_corrected_input = max_gamma_input_value_ * std::pow(normalized_input, inverse_gamma_factor);
    gamma_lookup_.at<uint8_t>(input) = static_cast<uint8_t>(std::round(gamma_corrected_input));
  }
}

cv::Mat GammaCorrector::run(const cv::Mat& input) const {
  CHECK_MAT(input, CV_8UC3, "gamma_correction_input", 3);
  cv::Mat output;
  cv::LUT(input, gamma_lookup_, output);
  return output;
}

cv::UMat GammaCorrector::run(const cv::UMat& input) const {
  CHECK_UMAT(input, CV_8UC3, "gamma_correction_input", 3);
  cv::UMat output;
  cv::UMat u_gamma_lookup = gamma_lookup_.getUMat(cv::ACCESS_READ);
  cv::LUT(input, u_gamma_lookup, output);
  return output;
}

}  // namespace panorama
}  // namespace data_product
}  // namespace bnr
