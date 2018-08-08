#include "io/ImageUtils.hpp"

#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

#include "gtest_utils/MatUtils.hpp"

using bnr_data_product::io::ImageUtils;
using bnr_data_product::gtest_utils::MatUtils;

static const char images_dir[] = "libs/gtest_utils/resources/images/";

TEST(ImageUtils, invalidLoadPaths) {
  std::string invalid_path = std::string(images_dir) + "DOES_NOT_EXIST.png";
  EXPECT_ANY_THROW(ImageUtils::loadGrayImageUint8(invalid_path));
  EXPECT_ANY_THROW(ImageUtils::loadRgbImageUint8(invalid_path));
  EXPECT_ANY_THROW(ImageUtils::loadGrayImageFloat(invalid_path));
  EXPECT_ANY_THROW(ImageUtils::loadRgbImageFloat(invalid_path));
}

TEST(ImageUtils, validLoadPaths) {
  ASSERT_NO_THROW(ImageUtils::loadGrayImageUint8(std::string(images_dir) + "gray_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadGrayImageUint8(std::string(images_dir) + "rgb_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadBgrImageUint8(std::string(images_dir) + "gray_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadBgrImageUint8(std::string(images_dir) + "rgb_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadRgbImageUint8(std::string(images_dir) + "gray_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadRgbImageUint8(std::string(images_dir) + "rgb_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadGrayImageFloat(std::string(images_dir) + "gray_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadGrayImageFloat(std::string(images_dir) + "rgb_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadBgrImageFloat(std::string(images_dir) + "gray_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadBgrImageFloat(std::string(images_dir) + "rgb_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadRgbImageFloat(std::string(images_dir) + "gray_2x2_uint8.png"));
  ASSERT_NO_THROW(ImageUtils::loadRgbImageFloat(std::string(images_dir) + "rgb_2x2_uint8.png"));
}

TEST(ImageUtils, loadGrayImageUint8) {
  cv::Mat loaded_image = ImageUtils::loadGrayImageUint8(std::string(images_dir) + "gray_2x2_uint8.png");
  cv::Mat expected_image = MatUtils::getGray2x2Uint8Mat();
  MatUtils::verifyMatsEQ<uint8_t>(expected_image, loaded_image);
}

TEST(ImageUtils, loadBgrImageUint8) {
  cv::Mat loaded_image = ImageUtils::loadBgrImageUint8(std::string(images_dir) + "rgb_2x2_uint8.png");
  cv::Mat expected_image = MatUtils::getBgr2x2Uint8Mat();
  MatUtils::verifyMatsEQ<uint8_t>(expected_image, loaded_image);
}

TEST(ImageUtils, loadRgbImageUint8) {
  cv::Mat loaded_image = ImageUtils::loadRgbImageUint8(std::string(images_dir) + "rgb_2x2_uint8.png");
  cv::Mat expected_image = MatUtils::getRgb2x2Uint8Mat();
  MatUtils::verifyMatsEQ<uint8_t>(expected_image, loaded_image);
}

TEST(ImageUtils, loadGrayImageFloat) {
  cv::Mat loaded_image = ImageUtils::loadGrayImageFloat(std::string(images_dir) + "gray_2x2_uint8.png");
  cv::Mat expected_image = MatUtils::getGray2x2FloatMat();
  MatUtils::verifyMatsEQ<float>(expected_image, loaded_image);
}

TEST(ImageUtils, loadBgrImageFloat) {
  cv::Mat loaded_image = ImageUtils::loadBgrImageFloat(std::string(images_dir) + "rgb_2x2_uint8.png");
  cv::Mat expected_image = MatUtils::getBgr2x2FloatMat();
  MatUtils::verifyMatsEQ<float>(expected_image, loaded_image);
}

TEST(ImageUtils, loadRgbImageFloat) {
  cv::Mat loaded_image = ImageUtils::loadRgbImageFloat(std::string(images_dir) + "rgb_2x2_uint8.png");
  cv::Mat expected_image = MatUtils::getRgb2x2FloatMat();
  MatUtils::verifyMatsEQ<float>(expected_image, loaded_image);
}

TEST(ImageUtils, invalidSaveEmptyMat) {
  cv::Mat emptyMat;
  std::string valid_path = std::string(images_dir) + "empty.png";
  EXPECT_THROW(ImageUtils::saveGrayImageUint8(emptyMat, valid_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveBgrImageUint8(emptyMat, valid_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveRgbImageUint8(emptyMat, valid_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveGrayImageFloat(emptyMat, valid_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveBgrImageFloat(emptyMat, valid_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveRgbImageFloat(emptyMat, valid_path), std::invalid_argument);
}

TEST(ImageUtils, invalidSaveWrongType) {
  cv::Mat gray_uint8_image = MatUtils::getGray2x2Uint8Mat();
  cv::Mat rgb_uint8_image = MatUtils::getRgb2x2Uint8Mat();
  cv::Mat gray_float_image = MatUtils::getGray2x2FloatMat();
  cv::Mat rgb_float_image = MatUtils::getRgb2x2FloatMat();
  // We should always fail before saving, so this path should not matter
  std::string save_path = std::string(images_dir) + "DOES_NOT_MATTER.png";

  EXPECT_THROW(ImageUtils::saveGrayImageUint8(rgb_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveGrayImageUint8(gray_float_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveGrayImageUint8(rgb_float_image, save_path), std::invalid_argument);

  EXPECT_THROW(ImageUtils::saveGrayImageFloat(gray_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveGrayImageFloat(rgb_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveGrayImageFloat(rgb_float_image, save_path), std::invalid_argument);

  EXPECT_THROW(ImageUtils::saveBgrImageUint8(gray_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveBgrImageUint8(gray_float_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveBgrImageUint8(rgb_float_image, save_path), std::invalid_argument);

  EXPECT_THROW(ImageUtils::saveBgrImageFloat(gray_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveBgrImageFloat(rgb_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveBgrImageFloat(gray_float_image, save_path), std::invalid_argument);

  EXPECT_THROW(ImageUtils::saveRgbImageUint8(gray_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveRgbImageUint8(gray_float_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveRgbImageUint8(rgb_float_image, save_path), std::invalid_argument);

  EXPECT_THROW(ImageUtils::saveRgbImageFloat(gray_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveRgbImageFloat(rgb_uint8_image, save_path), std::invalid_argument);
  EXPECT_THROW(ImageUtils::saveRgbImageFloat(gray_float_image, save_path), std::invalid_argument);
}

TEST(ImageUtils, saveGrayImageUint8) {
  // Save out the image
  cv::Mat image = MatUtils::getGray2x2Uint8Mat();
  std::string save_path = std::string(images_dir) + "SAVED_gray_2x2_uint8.png";
  ASSERT_NO_THROW(ImageUtils::saveGrayImageUint8(image, save_path));

  // Load it back it, verify it's the same
  ASSERT_NO_THROW(ImageUtils::loadGrayImageUint8(save_path));
  cv::Mat loaded_image = ImageUtils::loadGrayImageUint8(save_path);
  MatUtils::verifyMatsEQ<uint8_t>(image, loaded_image);
}

TEST(ImageUtils, saveBgrImageUint8) {
  // Save out the image
  cv::Mat image = MatUtils::getBgr2x2Uint8Mat();
  std::string save_path = std::string(images_dir) + "SAVED_bgr_2x2_uint8.png";
  ASSERT_NO_THROW(ImageUtils::saveBgrImageUint8(image, save_path));

  // Load it back it, verify it's the same
  ASSERT_NO_THROW(ImageUtils::loadBgrImageUint8(save_path));
  cv::Mat loaded_image = ImageUtils::loadBgrImageUint8(save_path);
  MatUtils::verifyMatsEQ<uint8_t>(image, loaded_image);
}

TEST(ImageUtils, saveRgbImageUint8) {
  // Save out the image
  cv::Mat image = MatUtils::getRgb2x2Uint8Mat();
  std::string save_path = std::string(images_dir) + "SAVED_rgb_2x2_uint8.png";
  ASSERT_NO_THROW(ImageUtils::saveRgbImageUint8(image, save_path));

  // Load it back it, verify it's the same
  ASSERT_NO_THROW(ImageUtils::loadRgbImageUint8(save_path));
  cv::Mat loaded_image = ImageUtils::loadRgbImageUint8(save_path);
  MatUtils::verifyMatsEQ<uint8_t>(image, loaded_image);
}

TEST(ImageUtils, saveGrayImageFloat) {
  // Save out the image
  cv::Mat image = MatUtils::getGray2x2FloatMat();
  std::string save_path = std::string(images_dir) + "SAVED_gray_2x2_float.png";
  ASSERT_NO_THROW(ImageUtils::saveGrayImageFloat(image, save_path));

  // Load it back it, verify it's the same
  ASSERT_NO_THROW(ImageUtils::loadGrayImageFloat(save_path));
  cv::Mat loaded_image = ImageUtils::loadGrayImageFloat(save_path);
  MatUtils::verifyMatsEQ<float>(image, loaded_image);
}

TEST(ImageUtils, saveBgrImageFloat) {
  // Save out the image
  cv::Mat image = MatUtils::getBgr2x2FloatMat();
  std::string save_path = std::string(images_dir) + "SAVED_rgb_2x2_float.png";
  ASSERT_NO_THROW(ImageUtils::saveBgrImageFloat(image, save_path));

  // Load it back it, verify it's the same
  ASSERT_NO_THROW(ImageUtils::loadBgrImageFloat(save_path));
  cv::Mat loaded_image = ImageUtils::loadBgrImageFloat(save_path);
  MatUtils::verifyMatsEQ<float>(image, loaded_image);
}

TEST(ImageUtils, saveRgbImageFloat) {
  // Save out the image
  cv::Mat image = MatUtils::getRgb2x2FloatMat();
  std::string save_path = std::string(images_dir) + "SAVED_rgb_2x2_float.png";
  ASSERT_NO_THROW(ImageUtils::saveRgbImageFloat(image, save_path));

  // Load it back it, verify it's the same
  ASSERT_NO_THROW(ImageUtils::loadRgbImageFloat(save_path));
  cv::Mat loaded_image = ImageUtils::loadRgbImageFloat(save_path);
  MatUtils::verifyMatsEQ<float>(image, loaded_image);
}

