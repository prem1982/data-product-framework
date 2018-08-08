#pragma once

#include <string>

#include "opencv2/core.hpp"

#include "io/Json.hpp"

namespace bnr_data_product {
namespace utils {

class JsonUtils {
 public:
  // Load in a json file
  static bnr_data_product::io::Json loadJson(const std::string& json_path);
  // If key exists and value is of the correct type return the value, else throw
  template<typename T>
  static T getJsonValue(const bnr_data_product::io::Json& input_json, const std::string& key);
};

}  // namespace utils
}  // namespace bnr_data_product
