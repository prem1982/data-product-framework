/**
 * @file label_reader_definitions.hpp
 *
 * @brief Header file for common definitions across the data_product 
 * label_reader library
 *
 * @copyright 2018 Bossa Nova Robotics. All rights reserved.
 */
#pragma once

#include <string>
#include "opencv2/core.hpp"

namespace bnr {
namespace data_product {

/**
 * @brief The location and contents of a symbol read off a label, as well
 * as as confidence value for the reading.
 */
struct ReadSymbol {
  /** The symbol read */
  std::string symbol_;
  /** The location of the symbol on the label */
  cv::Rect rect_;
  /** The confidence value of the reading */
  float confidence_;

  /**
   * @brief construct a <code>ReadSymbol</code>
   *
   * @param[in] symbol the symbol read
   * @param[in] rect the location of the symbol
   * @param[in] confidence the confidence of the read symbol
   */
  ReadSymbol(const std::string& symbol, const cv::Rect& rect, float confidence) :
    symbol_(symbol), rect_(rect), confidence_(confidence) {}
};

}  // namespace data_product
}  // namespace bnr
