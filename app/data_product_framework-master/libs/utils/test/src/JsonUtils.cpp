#include "utils/JsonUtils.hpp"

#include <stdexcept>
#include <string>

#include "opencv2/core.hpp"

#include "gtest/gtest.h"

using bnr_data_product::utils::JsonUtils;

static const char jsons_dir[] = "libs/gtest_utils/resources/jsons/";

TEST(JsonUtils, loadJson) {
  ASSERT_NO_THROW(JsonUtils::loadJson(std::string(jsons_dir) + "valid_simple.json"));
  ASSERT_NO_THROW(JsonUtils::loadJson(std::string(jsons_dir) + "invalid_size_1.json"));
  ASSERT_NO_THROW(JsonUtils::loadJson(std::string(jsons_dir) + "invalid_size_2.json"));
  EXPECT_THROW(JsonUtils::loadJson(std::string(jsons_dir) + "DOES_NOT_EXIST.json"),
      std::runtime_error);
}

TEST(JsonUtils, getJsonValue_json) {
  bnr_data_product::io::Json valid_json =
      JsonUtils::loadJson(std::string(jsons_dir) + "valid_simple.json");

  EXPECT_THROW(JsonUtils::getJsonValue<bnr_data_product::io::Json>(valid_json, "int_value"),
      std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<bnr_data_product::io::Json>(valid_json, "float_value"),
      std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<bnr_data_product::io::Json>(valid_json, "double_value"),
      std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<bnr_data_product::io::Json>(valid_json, "string_value"),
      std::runtime_error);
  EXPECT_NO_THROW(JsonUtils::getJsonValue<bnr_data_product::io::Json>(valid_json, "size_value"));
  EXPECT_NO_THROW(JsonUtils::getJsonValue<bnr_data_product::io::Json>(valid_json, "rect_value"));
  EXPECT_NO_THROW(JsonUtils::getJsonValue<bnr_data_product::io::Json>(valid_json, "rect2f_value"));
}

TEST(JsonUtils, getJsonValue_int) {
  bnr_data_product::io::Json valid_json =
      JsonUtils::loadJson(std::string(jsons_dir) + "valid_simple.json");

  ASSERT_NO_THROW(JsonUtils::getJsonValue<int32_t>(valid_json, "int_value"));
  EXPECT_THROW(JsonUtils::getJsonValue<int32_t>(valid_json, "float_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<int32_t>(valid_json, "double_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<int32_t>(valid_json, "size_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<int32_t>(valid_json, "string_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<int32_t>(valid_json, "rect_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<int32_t>(valid_json, "rect2f_value"), std::runtime_error);

  int32_t int_value = JsonUtils::getJsonValue<int>(valid_json, "int_value");
  EXPECT_FLOAT_EQ(1, int_value);
}

TEST(JsonUtils, getJsonValue_float) {
  bnr_data_product::io::Json valid_json =
      JsonUtils::loadJson(std::string(jsons_dir) + "valid_simple.json");

  ASSERT_NO_THROW(JsonUtils::getJsonValue<float>(valid_json, "int_value"));
  ASSERT_NO_THROW(JsonUtils::getJsonValue<float>(valid_json, "float_value"));
  ASSERT_NO_THROW(JsonUtils::getJsonValue<float>(valid_json, "double_value"));
  EXPECT_THROW(JsonUtils::getJsonValue<float>(valid_json, "string_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<float>(valid_json, "size_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<float>(valid_json, "rect_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<float>(valid_json, "rect2f_value"), std::runtime_error);

  float int_value = JsonUtils::getJsonValue<float>(valid_json, "int_value");
  EXPECT_FLOAT_EQ(1.0f, int_value);
  float float_value = JsonUtils::getJsonValue<float>(valid_json, "float_value");
  EXPECT_FLOAT_EQ(0.2f, float_value);
  float double_value = JsonUtils::getJsonValue<float>(valid_json, "double_value");
  EXPECT_FLOAT_EQ(0.03f, double_value);
}

TEST(JsonUtils, getJsonValue_double) {
  bnr_data_product::io::Json valid_json =
      JsonUtils::loadJson(std::string(jsons_dir) + "valid_simple.json");

  ASSERT_NO_THROW(JsonUtils::getJsonValue<double>(valid_json, "int_value"));
  ASSERT_NO_THROW(JsonUtils::getJsonValue<double>(valid_json, "float_value"));
  ASSERT_NO_THROW(JsonUtils::getJsonValue<double>(valid_json, "double_value"));
  EXPECT_THROW(JsonUtils::getJsonValue<double>(valid_json, "string_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<double>(valid_json, "size_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<double>(valid_json, "rect_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<double>(valid_json, "rect2f_value"), std::runtime_error);

  // Even if you read values in jsoncpp using .asDouble, it still only uses
  // float precision.
  double int_value = JsonUtils::getJsonValue<double>(valid_json, "int_value");
  EXPECT_FLOAT_EQ(1.0, int_value);
  double float_value = JsonUtils::getJsonValue<double>(valid_json, "float_value");
  EXPECT_FLOAT_EQ(0.2, float_value);
  double double_value = JsonUtils::getJsonValue<double>(valid_json, "double_value");
  EXPECT_FLOAT_EQ(0.03, double_value);
}

TEST(JsonUtils, getJsonValue_size) {
  bnr_data_product::io::Json valid_json =
      JsonUtils::loadJson(std::string(jsons_dir) + "valid_simple.json");
  bnr_data_product::io::Json invalid_size_json_one =
      JsonUtils::loadJson(std::string(jsons_dir) + "invalid_size_1.json");
  bnr_data_product::io::Json invalid_size_json_two =
      JsonUtils::loadJson(std::string(jsons_dir) + "invalid_size_2.json");

  EXPECT_THROW(JsonUtils::getJsonValue<cv::Size>(valid_json, "int_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Size>(valid_json, "float_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Size>(valid_json, "double_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Size>(valid_json, "string_value"), std::runtime_error);
  ASSERT_NO_THROW(JsonUtils::getJsonValue<cv::Size>(valid_json, "size_value"));
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Size>(valid_json, "rect_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Size>(valid_json, "rect2f_value"), std::runtime_error);

  cv::Size size_value = JsonUtils::getJsonValue<cv::Size>(valid_json, "size_value");
  EXPECT_EQ(4, size_value.height);
  EXPECT_EQ(5, size_value.width);

  EXPECT_THROW(JsonUtils::getJsonValue<cv::Size>(invalid_size_json_one, "size_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Size>(invalid_size_json_two, "size_value"), std::runtime_error);
}

TEST(JsonUtils, getJsonValue_rect) {
  bnr_data_product::io::Json valid_json =
      JsonUtils::loadJson(std::string(jsons_dir) + "valid_simple.json");

  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect>(valid_json, "int_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect>(valid_json, "float_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect>(valid_json, "double_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect>(valid_json, "string_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect>(valid_json, "size_value"), std::runtime_error);
  ASSERT_NO_THROW(JsonUtils::getJsonValue<cv::Rect>(valid_json, "rect_value"));
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect>(valid_json, "rect2f_value"), std::runtime_error);

  cv::Rect rect_value = JsonUtils::getJsonValue<cv::Rect>(valid_json, "rect_value");
  EXPECT_EQ(6, rect_value.x);
  EXPECT_EQ(7, rect_value.y);
  EXPECT_EQ(8, rect_value.width);
  EXPECT_EQ(9, rect_value.height);
}

TEST(JsonUtils, getJsonValue_rect2f) {
  bnr_data_product::io::Json valid_json =
      JsonUtils::loadJson(std::string(jsons_dir) + "valid_simple.json");

  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "int_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "float_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "double_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "string_value"), std::runtime_error);
  EXPECT_THROW(JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "size_value"), std::runtime_error);
  ASSERT_NO_THROW(JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "rect_value"));
  ASSERT_NO_THROW(JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "rect2f_value"));

  cv::Rect2f rect_value = JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "rect_value");
  EXPECT_FLOAT_EQ(6, rect_value.x);
  EXPECT_FLOAT_EQ(7, rect_value.y);
  EXPECT_FLOAT_EQ(8, rect_value.width);
  EXPECT_FLOAT_EQ(9, rect_value.height);

  cv::Rect2f rect2f_value = JsonUtils::getJsonValue<cv::Rect2f>(valid_json, "rect2f_value");
  EXPECT_FLOAT_EQ(2.5, rect2f_value.x);
  EXPECT_FLOAT_EQ(3.5, rect2f_value.y);
  EXPECT_FLOAT_EQ(5.5, rect2f_value.width);
  EXPECT_FLOAT_EQ(6.5, rect2f_value.height);
}

