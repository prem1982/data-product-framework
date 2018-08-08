#pragma once

#include <string>

#include "io/Json.hpp"
#include "utils/JsonUtils.hpp"

namespace bnr_data_product {
namespace utils {

// Reads the contents of a parameter file into a parameter struct and parses
class ParamsReader {
 public:
  explicit ParamsReader(const std::string& params_file) : params_(JsonUtils::loadJson(params_file)) {}
  explicit ParamsReader(bnr_data_product::io::Json params) : params_(params) {}
  // Parse from the root of params
  template<typename T>
  T run();
  // Parse from a given root within the params file
  template<typename T>
  T run(const bnr_data_product::io::Json& input_json);

 private:
  // The current params being used by this instance
  bnr_data_product::io::Json params_;
};

}  // namespace utils
}  // namespace bnr_data_product
