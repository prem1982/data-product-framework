#pragma once

#include <string>
#include <vector>

#include "opencv2/core.hpp"

#include "bnr_data_product/label_reader_definitions.hpp"

namespace bnr {
namespace data_product {
namespace label_reader {

// Combines the individual character outputs from OCR into final
// price strings. Uses domain knowledge to enhance results.
class PriceReaderPostProcessor {
 public:
  PriceReaderPostProcessor() noexcept {};
  std::string run(const std::vector<bnr::data_product::ReadSymbol>& read_symbols) const;

 private:
  static const char CENT_PREFIX[];
  static const int32_t SMALL_CHARACTER_SIZE = 5;
};

}  // namespace label_reader
}  // namespace data_product
}  // namespace bnr
