#include "gtest/gtest.h"

#include "gtest_utils/MatUtils.hpp"

#include "bnr_data_product/panorama/GammaCorrector.hpp"

using bnr::data_product::panorama::GammaCorrector;
using bnr_data_product::gtest_utils::MatUtils;

static const int32_t gamma_input_range = 256;

cv::Mat generateGammaTestMatrix() {
    cv::Mat test_matrix = cv::Mat(gamma_input_range, 1, CV_8UC3);
    for (int32_t input = 0; input < gamma_input_range; input++) {
        test_matrix.at<uint8_t>(input) = input;
    }
    return test_matrix;
}

// test that gamma = 1.0 has no effect
TEST(GammaCorrector, FixedScaleUnity) {
    cv::Mat inputs = generateGammaTestMatrix();
    GammaCorrector gc = GammaCorrector();

    cv::Mat results = gc.run(inputs);

    MatUtils::verifyMatsEQ<uint8_t>(inputs, results);

    cv::UMat uInputs = inputs.getUMat(cv::ACCESS_READ);
    cv::UMat uResults = gc.run(uInputs);
}

// test that gamma factor < 1 damps overall
// although the trend is visibile that the lower values are more damped, the rounding of converting
// back to integer values makes it difficult to test
TEST(GammaCorrector, FixedScaleSubUnity) {
    cv::Mat inputs = generateGammaTestMatrix();

    GammaCorrector gc = GammaCorrector(0.5);
    cv::Mat results = gc.run(inputs);

    MatUtils::verifyMatsGE<uint8_t>(inputs, results);
}
// test that gamma factor > 1 boosts overall
// although the trend is visibile that the lower values are more boosted, the rounding of converting
// back to integer values makes it difficult to test
TEST(GammaCorrector, FixedScaleSuperUnity) {
    cv::Mat inputs = generateGammaTestMatrix();

    GammaCorrector gc = GammaCorrector(2);
    cv::Mat results = gc.run(inputs);

    MatUtils::verifyMatsLE<uint8_t>(inputs, results);
}


// test that smaller gamma factors result in smaller gamma values
TEST(GammaCorrector, ComparativeScaleSubUnity) {
    cv::Mat inputs = generateGammaTestMatrix();

    GammaCorrector gc_small = GammaCorrector(0.5);
    cv::Mat large_gamma_result = gc_small.run(inputs);

    GammaCorrector gc_large = GammaCorrector(0.25);
    cv::Mat small_gamma_result = gc_large.run(inputs);

    MatUtils::verifyMatsLE<uint8_t>(small_gamma_result, large_gamma_result);
}

// test that larger gamma factors result in larger gamma values
TEST(GammaCorrector, ComparativeScaleSuperUnity) {
    cv::Mat inputs = generateGammaTestMatrix();

    GammaCorrector gc_large = GammaCorrector(4);
    cv::Mat large_gamma_result = gc_large.run(inputs);

    GammaCorrector gc_small = GammaCorrector(2);
    cv::Mat small_gamma_result = gc_small.run(inputs);

    MatUtils::verifyMatsLE<uint8_t>(small_gamma_result, large_gamma_result);
}

// Gamma must be positive.
TEST(GammaCorrector, FailsOnInvalidGamma) {
    ASSERT_THROW(GammaCorrector(0), std::invalid_argument);
    ASSERT_THROW(GammaCorrector(-1.0), std::invalid_argument);
}

// Images must be given as three-channel (8-bit) color
TEST(GammaCorrector, FailsOnInvalidMatrix) {
    cv::Mat bad_matrix_type = cv::Mat(gamma_input_range, 1, CV_32F);
    cv::Mat bad_matrix_channels = cv::Mat(gamma_input_range, 1, CV_8UC1);
    GammaCorrector gc = GammaCorrector();

    ASSERT_THROW(gc.run(bad_matrix_type), std::invalid_argument);
    ASSERT_THROW(gc.run(bad_matrix_channels), std::invalid_argument);
}
