#pragma once

#include <stdexcept>
#include <string>

#include "opencv2/core.hpp"

/*
 * @brief Check a function argument for correctness
 *
 * @param[in] x what to check
 * @param[in] s the message if the check fails
 */
inline
void CHECK_ARG(bool x, const std::string& s = "") {
  if (!x) throw std::invalid_argument(s);
}

/*
 * @brief Check a variable at runtime for correctness
 *
 * @param[in] x what to check
 * @param[in] s the message if the check fails
 */
inline
void CHECK_RUNTIME(bool x, const std::string& s = "") {
  if (!x) throw std::runtime_error(s);
}

/*
 * @brief Check a cv::Mat argument for expected qualities
 *
 * @param[in] input the cv::Mat to check
 * @param[in] expected_type the expected type of the cv::Mat
 * @param[in] variable_name the variable name of the cv::Mat, used for error messages
 * @param[in] expected_chans the number of expected channels, default 1
 * @param[in] expect_vector whether the cv::Mat is expected to be a vector (1 column)
 * @param[in] allow_empty whether the cv::Mat is allowed to be empty
 */
inline
void CHECK_MAT(const cv::Mat& input, int32_t expected_type, const std::string& variable_name,
    int32_t expected_chans = 1, bool expect_vector = false, bool allow_empty = false) {
  CHECK_ARG((input.type() == expected_type), variable_name + ": is of the wrong type");
  CHECK_ARG((input.channels() == expected_chans), variable_name + ": has incorrect number of channels");

  if (expect_vector) CHECK_ARG((input.cols == 1), variable_name + ": is not a vector");
  if (!allow_empty) CHECK_ARG(!input.empty(), variable_name + ": is empty");
}

/*
 * @brief Check a cv::UMat argument for expected qualities
 *
 * @param[in] input the cv::Mat to check
 * @param[in] expected_type the expected type of the cv::Mat
 * @param[in] variable_name the variable name of the cv::Mat, used for error messages
 * @param[in] expected_chans the number of expected channels, default 1
 * @param[in] expect_vector whether the cv::Mat is expected to be a vector (1 column)
 * @param[in] allow_empty whether the cv::Mat is allowed to be empty
 * @param[in] checkSize whether or not check the size
 * @param[in] optional size to use if checkSize is enabled
 */
inline
void CHECK_UMAT(const cv::UMat& input, int32_t expected_type, const std::string& variable_name,
    int32_t expected_chans = 1, bool expect_vector = false, bool allow_empty = false,
    bool checkSize = false, cv::Size expectedSize = cv::Size(1, 1)) {
  CHECK_ARG((input.type() == expected_type), variable_name + ": is of the wrong type");
  CHECK_ARG((input.channels() == expected_chans), variable_name + ": has incorrect number of channels");

  if (expect_vector) CHECK_ARG((input.cols == 1), variable_name + ": is not a vector");
  if (!allow_empty) CHECK_ARG(!input.empty(), variable_name + ": is empty");
  if (checkSize) CHECK_ARG(input.size() == expectedSize, variable_name + ": is of wrong size");
}

/*
 * @brief Check if two float values are approximately equal
 *
 * @param[in] a  first float
 * @param[in] b  second float
 * @param[in] epsilon tolerance for comparison
 *
 * @return True if a and b are within epsilon distance
 */
inline
bool FLOAT_EQ(float a, float b, float epsilon) {
  return std::abs(a - b) < epsilon;
}
