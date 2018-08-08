#include "gtest_utils/VectorUtils.hpp"

#include <vector>

#include "gtest/gtest.h"

namespace bnr_data_product {
namespace gtest_utils {

template<typename T>
void VectorUtils::verifyVectorsEqual(const std::vector<T>& vector1, const std::vector<T>& vector2) {
  ASSERT_EQ(vector1.size(), vector2.size());
  for (uint32_t iVal = 0; iVal < vector1.size(); iVal++) {
    EXPECT_EQ(vector1[iVal], vector2[iVal]);
  }
}
template void VectorUtils::verifyVectorsEqual<cv::Rect>(const std::vector<cv::Rect>& vector1,
    const std::vector<cv::Rect>& vector2);

}  // namespace gtest_utils
}  // namespace bnr_data_product
