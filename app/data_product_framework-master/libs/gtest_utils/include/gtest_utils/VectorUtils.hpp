#pragma once

#include <vector>

#include "opencv2/core.hpp"

namespace bnr_data_product {
namespace gtest_utils {

class VectorUtils {
 public:
  // Verifies that two std::vectors are identical
  template<typename T>
  static void verifyVectorsEqual(const std::vector<T>& vector1, const std::vector<T>& vector2);
};

}  // namespace gtest_utils
}  // namespace bnr_data_product
