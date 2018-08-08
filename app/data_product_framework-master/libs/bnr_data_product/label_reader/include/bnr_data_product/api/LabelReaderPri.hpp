#pragma once

#include <vector>

#include "opencv2/core.hpp"

#include "bnr_data_product/label_reader/PriceDetector.hpp"
#include "bnr_data_product/label_reader/PriceReader.hpp"
#include "bnr_data_product/label_reader_definitions.hpp"

namespace bnr {
namespace data_product {

// Private implementation of the LabelReader, implements the public API
class LabelReaderPri {
 public:
  struct Params {
    float scale_factor_;
    cv::Rect2f nominal_patch_;
    label_reader::PriceDetector::Params price_detector_params_;
    label_reader::PriceReader::Params price_reader_params_;

    Params(float scale_factor,
        const cv::Rect2f& nominal_patch,
        const label_reader::PriceDetector::Params& price_detector_params,
        const label_reader::PriceReader::Params& price_reader_params)
        : scale_factor_(scale_factor), nominal_patch_(nominal_patch), price_detector_params_(price_detector_params),
        price_reader_params_(price_reader_params) {}
  };

  explicit LabelReaderPri(const Params& params)
      : params_(params), price_detector_(params.price_detector_params_, params.scale_factor_),
      price_reader_(params.price_reader_params_, params.scale_factor_) {}
  bnr::data_product::ReadSymbol run(const cv::Mat& input_img) const;

 private:
  Params params_;
  label_reader::PriceDetector price_detector_;
  label_reader::PriceReader price_reader_;
  bnr::data_product::ReadSymbol postProcessMultiplePatches(
      const cv::Mat& label_img, const bnr::data_product::label_reader::RoiImage& roi_image_bundle,
      const std::vector<bnr::data_product::ReadSymbol>& read_prices) const;
};


}  // namespace data_product
}  // namespace bnr

