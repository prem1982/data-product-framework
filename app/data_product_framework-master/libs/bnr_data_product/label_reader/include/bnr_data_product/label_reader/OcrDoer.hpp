#pragma once

#include <memory>
#include <vector>

#include "leptonica/allheaders.h"
#include "opencv2/core.hpp"
#include "tesseract/baseapi.h"

#include "bnr_data_product/label_reader_definitions.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

// Performs OCR on a cropped label after MSER detects boxes and the image is de-noised
class OcrDoer {
 public:
  OcrDoer();
  std::vector<bnr::data_product::ReadSymbol> run(const cv::Mat& detected_price_crop) const;

 private:
  static const char TESSERACT_DATA_PATH[];
  static const char TESSERACT_CHAR_WHITELIST[];
  static const char TESSERACT_LANG[];

  std::shared_ptr<tesseract::TessBaseAPI> tess_api_instance_;
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr

