#include "bnr_data_product/label_reader/OcrDoer.hpp"

#include <string>
#include <memory>
#include <vector>
#include "opencv2/imgproc.hpp"
#include "macros.hpp"
#include "io/ImageUtils.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

const char OcrDoer::TESSERACT_DATA_PATH[] = "/usr/share/tesseract-ocr/tessdata";
const char OcrDoer::TESSERACT_CHAR_WHITELIST[] = "01234567890.";
const char OcrDoer::TESSERACT_LANG[] = "eng";

OcrDoer::OcrDoer() {
  tess_api_instance_ = std::make_shared<tesseract::TessBaseAPI>();
  CHECK_RUNTIME(!tess_api_instance_->Init(TESSERACT_DATA_PATH,
      TESSERACT_LANG, tesseract::OEM_TESSERACT_ONLY),
      "tesseract instance initialization failed");

  tess_api_instance_->SetPageSegMode(tesseract::PSM_SINGLE_WORD);
  tess_api_instance_->SetVariable("tessedit_char_whitelist", TESSERACT_CHAR_WHITELIST);
}

std::vector<bnr::data_product::ReadSymbol> OcrDoer::run(const cv::Mat& detected_price_crop) const {
  CHECK_MAT(detected_price_crop, CV_8U, "OcrDoer input detected_price_crop");

  // Run tesseract
  tess_api_instance_->ClearAdaptiveClassifier();  // Clear state from previous results
  tess_api_instance_->SetImage(reinterpret_cast<uchar*>(detected_price_crop.data), detected_price_crop.size().width,
      detected_price_crop.size().height, detected_price_crop.channels(),
      (int32_t)detected_price_crop.step1());
  tess_api_instance_->Recognize(0);

  // Read tesseract results
  tesseract::ResultIterator* result_iterator = tess_api_instance_->GetIterator();
  tesseract::PageIteratorLevel level = tesseract::RIL_SYMBOL;
  std::vector<ReadSymbol> read_symbols;

  /* structured as per example API usage here :
  https://github.com/tesseract-ocr/tesseract/wiki/APIExample */
  do {
    // If this character is empty, ignore it
    const char* character_char = result_iterator->GetUTF8Text(level);
    if (character_char == nullptr) {
      continue;
    }

    // Parse out useful info
    const std::string character(character_char);
    int32_t x1, y1, x2, y2;
    result_iterator->BoundingBox(level, &x1, &y1, &x2, &y2);
    const cv::Rect rect(x1, y1, x2-x1, y2-y1);
    const float conf = result_iterator->Confidence(level);
    // Save the symbol info, move on to next result
    read_symbols.emplace_back(character, rect, conf);
  } while (result_iterator->Next(level));

  return read_symbols;
}

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
