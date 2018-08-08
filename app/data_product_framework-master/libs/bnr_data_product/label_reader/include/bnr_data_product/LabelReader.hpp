/**
 * @file LabelReader.hpp
 *
 * @brief Header file for Bossa Nova's Data Product Team's LabelReader,
 * part of the data_product library.
 *
 * @copyright 2018 Bossa Nova Robotics. All rights reserved.
 */
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "opencv2/core.hpp"

#include "bnr_data_product/label_reader_definitions.hpp"

namespace bnr {
namespace data_product {

class LabelReaderPri;

/**
 * @brief A LabelReader takes in the crop of a label and reads its contents
 */
class LabelReader {
 public:
  /**
   * @brief Construct a <code>LabelReader</code>
   *
   * @param[in] paramsJson the path to a JSON parameter file
   */
  explicit LabelReader(const std::string& paramsJson);
  /**
   * @brief Run the <code>LabelReader</code> on a label
   *
   * @param[in] input_img a 3 channel BGR image crop of a label to read
   *
   * @return The locations and contents of prices on the label
   */
  bnr::data_product::ReadSymbol run(const cv::Mat& input_img) const;

 private:
  std::shared_ptr<LabelReaderPri> label_reader_pri_;
};

}  // namespace data_product
}  // namespace bnr

