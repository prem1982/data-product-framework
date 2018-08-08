#include "macros.hpp"

#include <stdexcept>

#include "gtest/gtest.h"
#include "opencv2/core.hpp"

#include "gtest_utils/MatUtils.hpp"

using bnr_data_product::gtest_utils::MatUtils;

TEST(macros, checkArg) {
  EXPECT_NO_THROW(CHECK_ARG(true));
  EXPECT_THROW(CHECK_ARG(false), std::invalid_argument);
}

TEST(macros, checkRuntime) {
  EXPECT_NO_THROW(CHECK_RUNTIME(true));
  EXPECT_THROW(CHECK_RUNTIME(false), std::runtime_error);
}

TEST(macros, checkMat_type) {
  for (const auto& mat_type_1 : MatUtils::mat_types) {
    const cv::Mat mat = cv::Mat::zeros(2, 2, mat_type_1);
    for (const auto& mat_type_2 : MatUtils::mat_types) {
      if (mat_type_1 == mat_type_2) {
        EXPECT_NO_THROW(CHECK_MAT(mat, mat_type_2, "checkMat_type mat", mat.channels()));
      } else {
        EXPECT_THROW(CHECK_MAT(mat, mat_type_2, "checkMat_type mat", mat.channels()),
            std::invalid_argument);
      }
    }
  }
}

TEST(macros, checkMat_chans) {
  for (const auto& mat_type : MatUtils::mat_types) {
    const cv::Mat mat = cv::Mat::zeros(2, 2, mat_type);
    for (int32_t numChans = 0; numChans < 5; numChans++) {
      if (mat.channels() == numChans) {
        EXPECT_NO_THROW(CHECK_MAT(mat, mat_type, "checkMat_chans mat", numChans));
      } else {
        EXPECT_THROW(CHECK_MAT(mat, mat_type, "checkMat_chans mat", numChans),
            std::invalid_argument);
      }
    }
  }
}

TEST(macros, checkMat_expectVector) {
  const cv::Mat not_vector = cv::Mat::zeros(2, 2, CV_32FC1);
  const cv::Mat vector = cv::Mat::zeros(2, 1, CV_32FC1);
  const cv::Mat vector_transpose = cv::Mat::zeros(1, 2, CV_32FC1);

  EXPECT_NO_THROW(CHECK_MAT(not_vector, CV_32FC1, "checkMat_expectVector not_vector",
      1, false));
  EXPECT_THROW(CHECK_MAT(not_vector, CV_32FC1, "checkMat_expectVector not_vector", 1, true),
      std::invalid_argument);

  EXPECT_NO_THROW(CHECK_MAT(vector, CV_32FC1, "checkMat_expectVector vector", 1, false));
  EXPECT_NO_THROW(CHECK_MAT(vector, CV_32FC1, "checkMat_expectVector vector", 1, true));

  EXPECT_NO_THROW(CHECK_MAT(vector_transpose, CV_32FC1, "checkMat_expectVector vector_transpose",
      1, false));
  EXPECT_THROW(CHECK_MAT(vector_transpose, CV_32FC1, "checkMat_expectVector vector_transpose",
      1, true), std::invalid_argument);
}

TEST(macros, checkMat_allowEmpty) {
  const cv::Mat not_empty = cv::Mat::zeros(2, 2, CV_32FC1);
  const cv::Mat empty(0, 0, CV_32FC1);

  EXPECT_NO_THROW(CHECK_MAT(not_empty, CV_32FC1, "checkMat_allowEmpty not_empty",
      1, false, false));
  EXPECT_NO_THROW(CHECK_MAT(not_empty, CV_32FC1, "checkMat_allowEmpty not_empty",
      1, false, true));

  EXPECT_THROW(CHECK_MAT(empty, CV_32FC1, "checkMat_allowEmpty empty", 1, false, false),
      std::invalid_argument);
  EXPECT_NO_THROW(CHECK_MAT(empty, CV_32FC1, "checkMat_allowEmpty empty", 1, false, true));
}


TEST(macros, floatEquals) {
  EXPECT_TRUE(FLOAT_EQ(1.0f, 1.0f, .000001f));
  EXPECT_TRUE(FLOAT_EQ(1.0f, 1.1f, .11f));
  EXPECT_FALSE(FLOAT_EQ(1.0f, 1.1f, .10f));
}
