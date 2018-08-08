#include "bnr_data_product/label_reader/PriceReaderPostProcessor.hpp"

#include <string>
#include <vector>

#include "macros.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

const char PriceReaderPostProcessor::CENT_PREFIX[] = "0.";

std::string PriceReaderPostProcessor::run(
  const std::vector<bnr::data_product::ReadSymbol>& read_symbols) const {
  // Find the "."
  int32_t period_pos = -1;
  int32_t period_count = 0;
  for (uint32_t i = 0; i < read_symbols.size(); i++) {
    if (read_symbols[i].symbol_ == ".") {
      period_pos = i;
      period_count+=1;
    }
  }

  int32_t start_pos = 0;
  int32_t end_pos = read_symbols.size() - 1;  // 0-indexed for easy use with other *_pos vars
  std::string prefix = "";

  // We have a "." and at least two numbers after the "." --> dollar price
  if (period_count == 1 && period_pos >= 1 && (end_pos - period_pos) >= 2) {
        // If the $ has been incorrectly read as a number by tesseract,
        // remove it from first position and replace with $
        if (period_pos >= 2 && std::abs(read_symbols[0].rect_.height - read_symbols[1].rect_.height) >
             SMALL_CHARACTER_SIZE) {
            start_pos = 1;
        }
        // Trim the cent value after the period to 2 digits
        if (end_pos - period_pos > 2) {
          end_pos = period_pos + 2;
        }
  // We don't have a dollar price --> check for a cent price
  } else if (period_count == 0 && end_pos >= 1) {
    end_pos = 1;
    prefix = CENT_PREFIX;
  // Anything else is invalid --> return empty text_read
  } else {
    end_pos = -1;
  }

  std::string text_read(prefix);
  for (int32_t i = start_pos; i < end_pos + 1; i++) {
    text_read.append(read_symbols[i].symbol_);
  }
  return text_read;
}

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
