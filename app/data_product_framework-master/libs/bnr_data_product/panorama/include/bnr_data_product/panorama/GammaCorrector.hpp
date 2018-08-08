#pragma once

#include "opencv2/core.hpp"

namespace bnr {
namespace data_product {
namespace panorama {

class GammaCorrector {
 public:
  /**
   * @brief Create a gamma correction lookup table.
   *
   * Non-positive gamma values will result in an error.
   * A gamma factor of 1 has no effect.
   * A gamma factor > 1 has a logarithmic curve  whose values are strictly GREATER THAN OR EQUAL TO the inputs. This
   *   boosting is particularly strong at low values, acting something like a low-pass filter. Larger gamma factors are
   *   both more boosted in general and more unequally boosted, asymptotically approaching an all-white image.
   * A gamma factor < 1 has an exponential curve whose values are strictly LESS THAN OR EQUAL TO the inputs. This
   *   damping is particularly strong at low values, acting something like a high-pass filter. Smaller gamma factors are
   *   both more damped in general and more unequally damped, asymptotically approaching an all-black image.
   *
   * @param[in] gamma Gamma correction coefficient, default 1.0. Must be positive.
   */
  explicit GammaCorrector(double gamma = 1.0);

  /**
   * @brief Apply the configured gamma correction to the input image
   *
   * @param[in] input Source image. Must be three-channel (8 bit) color.
   *
   * @return gamma-corrected image of the same size, channels, and color mode
   */
  cv::Mat run(const cv::Mat& input) const;
  cv::UMat run(const cv::UMat& input) const;

 private:
  static constexpr int32_t max_gamma_input_value_ = 255;  // 8-bit gamma
  static constexpr int32_t gamma_input_range_ = 256;  // 8-bit gamma -> note, is |8 bit int| + 1

  cv::Mat gamma_lookup_;
};  // class GammaCorrection

}  // namespace panorama
}  // namespace data_product
}  // namespace bnr
