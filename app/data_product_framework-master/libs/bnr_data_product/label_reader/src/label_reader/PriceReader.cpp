#include "bnr_data_product/label_reader/PriceReader.hpp"

#include <string>
#include <vector>
#include "io/ImageUtils.hpp"
#include "macros.hpp"
#include "utils/RectUtils.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

std::vector<bnr::data_product::ReadSymbol> PriceReader::run(const cv::Mat& label_img,
    const std::vector<cv::Rect>& detected_prices) const {
  // Rescale all our rects by the rescale factor
  std::vector<cv::Rect> rescaled_prices;
  for (const auto& detected_price : detected_prices) {
    // Rescale the rect --> if it is outside the image, ignore
    const cv::Rect rescaled_price = bnr_data_product::utils::RectUtils::rescaleRect(
        detected_price, scale_factor_);
    if ((rescaled_price & cv::Rect(0, 0, label_img.cols, label_img.rows)).area() > 0) {
      rescaled_prices.push_back(rescaled_price);
    }
  }
  std::vector<bnr::data_product::ReadSymbol> final_symbols = runAllIterations(label_img, rescaled_prices);
  // Run the price reading on the rescaled prices
  return final_symbols;
}

std::vector<bnr::data_product::ReadSymbol> PriceReader::runAllIterations(const cv::Mat& label_img,
    const std::vector<cv::Rect>& rescaled_prices, int32_t num_iters) const {
  std::vector<bnr::data_product::ReadSymbol> final_symbols =
      runSingleIteration(label_img, rescaled_prices);

  // Check for a new iteration
  if (num_iters < MAX_NUM_ITERATIONS) {
    std::vector<cv::Rect> widened_rects;
    std::vector<bnr::data_product::ReadSymbol> passing_symbols;

    for (const auto& final_symbol : final_symbols) {
      const std::string final_text = final_symbol.symbol_;

      // If we have the case of a period with only one character after, we know we missed a
      // character. Therefore we widen our box and re-run
      if ((final_text.find('.') + 1) == final_text.length() - 1 && final_text.length() >= 4) {
        const cv::Rect text_rect = final_symbol.rect_;
        // At most we can widen to the edge of the image
        int32_t widened_width = std::min(text_rect.width + WIDEN_WIDTH, label_img.cols - text_rect.x);
        const cv::Rect widened_rect(text_rect.x, text_rect.y, widened_width, text_rect.height);
        widened_rects.push_back(widened_rect);
        // Recursively run on the widened rects and append their results to the passing symbols
        std::vector<bnr::data_product::ReadSymbol> new_final_symbols =
            runAllIterations(label_img, widened_rects, num_iters + 1);
        passing_symbols.insert(passing_symbols.end(), new_final_symbols.begin(), new_final_symbols.end());
        // Otherwise just keep the passing symbol
      } else {
        passing_symbols.push_back(final_symbol);
      }
    }

    final_symbols = passing_symbols;
  }
  return final_symbols;
}


std::vector<bnr::data_product::ReadSymbol> PriceReader::runSingleIteration(const cv::Mat& label_img,
    const std::vector<cv::Rect>& rescaled_prices) const {
  CHECK_MAT(label_img, CV_8U, "PriceReader input label_img");

  std::vector<bnr::data_product::ReadSymbol> final_symbols;
  for (const auto& rescaled_price : rescaled_prices) {
    // If our detection is outside the image, skip it
    if (!bnr_data_product::utils::RectUtils::checkWithinImage(rescaled_price,
        label_img.rows, label_img.cols)) {
      continue;
    }
    // Run the pre-processing, OCR, and post-processing to get the final text
    const cv::Mat price_crop = pre_processor_.run(label_img, rescaled_price);
    const std::vector<bnr::data_product::ReadSymbol> read_symbols = ocr_doer_.run(price_crop);
    const std::string final_text = post_processor_.run(read_symbols);

    // If we have text, create the ReadSymbol and store
    if (!final_text.empty()) {
      const bnr::data_product::ReadSymbol final_symbol(final_text, rescaled_price, 1.0f);
      final_symbols.push_back(final_symbol);
    }
  }

  return final_symbols;
}

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
