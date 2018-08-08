#include "utils/RectUtils.hpp"

#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

void checkWithinImageOfAllRects(const std::vector<cv::Rect>& fails, const std::vector<cv::Rect>& passes,
    int32_t img_height, int32_t img_width);
void checkAreaOfAllRects(const std::vector<cv::Rect>& fails, const std::vector<cv::Rect>& passes,
    int32_t min_area, int32_t max_area);
void checkAspectRatioOfAllRects(const std::vector<cv::Rect>& fails, const std::vector<cv::Rect>& passes,
    float min_aspect_ratio, float max_aspect_ratio);

using bnr_data_product::utils::RectUtils;

const cv::Rect square = cv::Rect(0, 0, 2, 2);
const cv::Rect wide = cv::Rect(0, 0, 4, 2);
const cv::Rect very_wide = cv::Rect(0, 0, 8, 2);
const cv::Rect tall = cv::Rect(0, 0, 2, 4);
const cv::Rect very_tall = cv::Rect(0, 0, 2, 8);

const cv::Rect square_shifted = cv::Rect(2, 2, 2, 2);

const cv::Rect zero_width = cv::Rect(1, 1, 0, 1);
const cv::Rect zero_height = cv::Rect(1, 1, 1, 0);

TEST(RectUtils, getAspectRatio) {
  EXPECT_THROW(RectUtils::getAspectRatio(zero_width), std::invalid_argument);
  EXPECT_FLOAT_EQ(0.0f, RectUtils::getAspectRatio(zero_height));

  const float square_aspect_ratio = RectUtils::getAspectRatio(square);
  EXPECT_FLOAT_EQ(1.0f, square_aspect_ratio);

  const float wide_aspect_ratio = RectUtils::getAspectRatio(wide);
  EXPECT_FLOAT_EQ(0.5f, wide_aspect_ratio);

  const float very_wide_aspect_ratio = RectUtils::getAspectRatio(very_wide);
  EXPECT_FLOAT_EQ(0.25f, very_wide_aspect_ratio);

  const float tall_aspect_ratio = RectUtils::getAspectRatio(tall);
  EXPECT_FLOAT_EQ(2.0f, tall_aspect_ratio);

  const float very_tall_aspect_ratio = RectUtils::getAspectRatio(very_tall);
  EXPECT_FLOAT_EQ(4.0f, very_tall_aspect_ratio);

  const float square_shifted_aspect_ratio = RectUtils::getAspectRatio(square_shifted);
  EXPECT_FLOAT_EQ(1.0f, square_shifted_aspect_ratio);
}

TEST(RectUtils, addBuffer) {
  const cv::Rect square_buffered_one = cv::Rect(0, 0, 4, 4);
  const cv::Rect square_shifted_buffered_one = cv::Rect(1, 1, 4, 4);

  const cv::Rect square_buffered_one_result = RectUtils::addBuffer(square, 1);
  const cv::Rect square_shifted_buffered_one_result = RectUtils::addBuffer(square_shifted, 1);

  EXPECT_EQ(square_buffered_one, square_buffered_one_result);
  EXPECT_EQ(square_shifted_buffered_one, square_shifted_buffered_one_result);
}

TEST(RectUtils, rescaleSanityTest) {
  const cv::Rect square_doubled = cv::Rect(0, 0, 4, 4);
  const cv::Rect square_shifted_doubled = cv::Rect(4, 4, 4, 4);

  const cv::Rect square_doubled_result = RectUtils::rescaleRect(square, 2.0f);
  const cv::Rect square_shifted_doubled_result = RectUtils::rescaleRect(square_shifted, 2.0f);
  EXPECT_EQ(square_doubled, square_doubled_result);
  EXPECT_EQ(square_shifted_doubled, square_shifted_doubled_result);
}

TEST(RectUtils, rescaleRoundTest) {
  const cv::Rect square_doubled = cv::Rect(0, 0, 4, 4);
  const cv::Rect square_shifted_doubled = cv::Rect(4, 4, 4, 4);

  const cv::Rect square_almost_doubled_result = RectUtils::rescaleRect(square, 1.75f);
  const cv::Rect square_shifted_almost_doubled_result = RectUtils::rescaleRect(square_shifted, 1.75f);
  EXPECT_EQ(square_doubled, square_almost_doubled_result);
  EXPECT_EQ(square_shifted_doubled, square_shifted_almost_doubled_result);
}

TEST(RectUtils, shiftScaleSanityTest) {
  const cv::Rect square_shifted_right = cv::Rect(2, 0, 2, 2);
  const cv::Rect square_shifted_left = cv::Rect(-2, 0, 2, 2);
  const cv::Rect square_shifted_up = cv::Rect(0, 1, 2, 2);
  const cv::Rect square_shifted_down = cv::Rect(0, -1, 2, 2);

  const cv::Rect square_shifted_right_result = RectUtils::shiftAndRescaleRect<int>(square, 2, 0, 1.0);
  const cv::Rect square_shifted_left_result = RectUtils::shiftAndRescaleRect<int>(square, -2, 0, 1.0);
  const cv::Rect square_shifted_up_result = RectUtils::shiftAndRescaleRect<int>(square, 0, 1, 1.0);
  const cv::Rect square_shifted_down_result = RectUtils::shiftAndRescaleRect<int>(square, 0, -1, 1.0);

  EXPECT_EQ(square_shifted_right, square_shifted_right_result);
  EXPECT_EQ(square_shifted_left, square_shifted_left_result);
  EXPECT_EQ(square_shifted_up, square_shifted_up_result);
  EXPECT_EQ(square_shifted_down, square_shifted_down_result);
}

TEST(RectUtils, shiftRoundTest) {
  const cv::Rect square = cv::Rect(1.1, 1.0, 2.0, 2.1);
  const cv::Rect square_shifted_right = cv::Rect(2, 1, 2, 2);
  const cv::Rect square_shifted_right_result = RectUtils::shiftAndRescaleRect<int>(square, 1, 0, 1.0);
  EXPECT_EQ(square_shifted_right, square_shifted_right_result);
}

TEST(RectUtils, shiftAndRescaleRectTest) {
  const cv::Rect square_shifted_doubled = cv::Rect(4, 4, 4, 4);
  const cv::Rect square_shifted_doubled_result = RectUtils::shiftAndRescaleRect<int>(square, 2, 2, 2);
  EXPECT_EQ(square_shifted_doubled, square_shifted_doubled_result);

  const cv::Rect rect = cv::Rect(0, 0, 6, 6.4);
  const cv::Rect rect_shifted_scaled = cv::Rect(-1, -1, 3, 3);
  const cv::Rect rect_shifted_scaled_result = RectUtils::shiftAndRescaleRect<int>(rect, -1, -1, .5);
  EXPECT_EQ(rect_shifted_scaled, rect_shifted_scaled_result);
}

TEST(RectUtils, rectUnionSanityTest) {
  { // empty case
    std::vector<cv::Rect> rects;
    EXPECT_THROW(RectUtils::rectUnion<int>(rects), std::invalid_argument);
    std::vector<cv::Rect2f> rects2;
    EXPECT_THROW(RectUtils::rectUnion<float>(rects2), std::invalid_argument);
  }
  // int case
  {
    const cv::Rect rect = cv::Rect(0, 0, 2, 3);
    std::vector<cv::Rect> rects;
    rects.push_back(rect);
    const cv::Rect rect_union_result = RectUtils::rectUnion<int>(rects);
    EXPECT_EQ(rect, rect_union_result);
  }

  // float case
  {
    const cv::Rect2f rect = cv::Rect(0.0, 0.0, .2, .3);
    std::vector<cv::Rect2f> rects;
    rects.push_back(rect);
    const cv::Rect2f rect_union_result = RectUtils::rectUnion<float>(rects);
    EXPECT_EQ(rect, rect_union_result);
  }
}

TEST(RectUtils, rectUnionIntTest) {
  const cv::Rect rect1 = cv::Rect(0, 0, 5, 4);
  const cv::Rect rect2 = cv::Rect(-1, 2, 7, 6);
  std::vector<cv::Rect> rects;
  rects.push_back(rect1);
  rects.push_back(rect2);
  const cv::Rect rect_union = cv::Rect(-1, 0, 7, 8);
  const cv::Rect rect_union_result = RectUtils::rectUnion<int>(rects);
  EXPECT_EQ(rect_union, rect_union_result);
}

TEST(RectUtils, rectUnionFloatTest) {
  const cv::Rect2f rect1 = cv::Rect2f(0, 0, .5, .4);
  const cv::Rect2f rect2 = cv::Rect2f(-.1, .2, .7, .6);
  std::vector<cv::Rect2f> rects;
  rects.push_back(rect1);
  rects.push_back(rect2);
  const cv::Rect2f rect_union = cv::Rect2f(-.1, 0, .7, .8);
  const cv::Rect2f rect_union_result = RectUtils::rectUnion<float>(rects);
  EXPECT_EQ(rect_union, rect_union_result);
}

TEST(RectUtils, checkWithinImage) {
  const std::vector<cv::Rect> fails_5_4 = {very_wide, very_tall};
  const std::vector<cv::Rect> passes_5_4 = {square, wide, tall};
  checkWithinImageOfAllRects(fails_5_4, passes_5_4, 5, 4);
}

TEST(RectUtils, checkWithinImageNegative) {
  const cv::Rect negative_fail = cv::Rect(-1, 0, 1, 1);
  EXPECT_EQ(false, RectUtils::checkWithinImage(negative_fail, 3, 3));
}

TEST(RectUtils, checkArea) {
  const std::vector<cv::Rect> fails_5_10 = {square, very_wide, very_tall, zero_width, zero_height};
  const std::vector<cv::Rect> passes_5_10 = {wide, tall};
  checkAreaOfAllRects(fails_5_10, passes_5_10, 5, 10);
}

TEST(RectUtils, checkAspectRatio) {
  EXPECT_THROW(RectUtils::checkAspectRatio(zero_width, 0.0f, 0.0f), std::invalid_argument);
  const std::vector<cv::Rect> fails_third_three = {very_wide, very_tall, zero_height};
  const std::vector<cv::Rect> passes_third_three = {square, wide, tall};
  checkAspectRatioOfAllRects(fails_third_three, passes_third_three, 0.33f, 3.0f);
}

void checkWithinImageOfAllRects(const std::vector<cv::Rect>& fails, const std::vector<cv::Rect>& passes,
    int32_t img_height, int32_t img_width) {
  for (const auto& fail : fails) {
    EXPECT_EQ(false, RectUtils::checkWithinImage(fail, img_height, img_width));
  }
  for (const auto& pass : passes) {
    EXPECT_EQ(true, RectUtils::checkWithinImage(pass, img_height, img_width));
  }
}

void checkAreaOfAllRects(const std::vector<cv::Rect>& fails, const std::vector<cv::Rect>& passes,
    int32_t min_area, int32_t max_area) {
  for (const auto& fail : fails) {
    EXPECT_EQ(false, RectUtils::checkArea(fail, min_area, max_area));
  }
  for (const auto& pass : passes) {
    EXPECT_EQ(true, RectUtils::checkArea(pass, min_area, max_area));
  }
}

void checkAspectRatioOfAllRects(const std::vector<cv::Rect>& fails, const std::vector<cv::Rect>& passes,
    float min_aspect_ratio, float max_aspect_ratio) {
  for (const auto& fail : fails) {
    EXPECT_EQ(false, RectUtils::checkAspectRatio(fail, min_aspect_ratio, max_aspect_ratio));
  }
  for (const auto& pass : passes) {
    EXPECT_EQ(true, RectUtils::checkAspectRatio(pass, min_aspect_ratio, max_aspect_ratio));
  }
}
