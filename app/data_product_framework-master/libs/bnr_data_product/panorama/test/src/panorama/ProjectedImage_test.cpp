#include "gtest/gtest.h"

#include "gtest_utils/MatUtils.hpp"

#include "bnr_data_product/panorama/ProjectedImage.hpp"

using bnr::data_product::panorama::ProjectedImage;
using bnr_data_product::gtest_utils::MatUtils;

TEST(ProjectedImage, nonEmptyMat) {
  cv::UMat image(10, 10, CV_8UC4);
  cv::Point2f position(0.0f, 0.0f);
  ProjectedImage pi(image, position, 1.0f, cv::Scalar(0));
  ASSERT_FALSE(pi.image().empty());
}


TEST(ProjectedImage, getters) {
  cv::UMat image(10, 10, CV_8UC4);
  cv::Point2f position(0.0f, 0.0f);
  ProjectedImage pi(image, position, 1.0f, cv::Scalar(0));
  MatUtils::verifyMatsEQ<uint8_t>(pi.image().getMat(cv::ACCESS_READ), image.getMat(cv::ACCESS_READ));
  ASSERT_EQ(pi.position(), position);
}
