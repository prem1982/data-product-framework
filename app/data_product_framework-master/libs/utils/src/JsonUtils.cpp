#include "utils/JsonUtils.hpp"

#include <fstream>
#include <string>

#include "macros.hpp"

namespace bnr_data_product {
namespace utils {

using bnr_data_product::io::Json;

Json JsonUtils::loadJson(const std::string& json_path) {
  Json input_json;

  std::ifstream json_stream(json_path);
  CHECK_RUNTIME(json_stream.is_open(), "Unable to open JSON file: " + json_path);
  json_stream >> input_json;
  json_stream.close();

  return input_json;
}

// getJsonValue, primitive C++ types
template<>
Json JsonUtils::getJsonValue<Json>(const Json& input_json, const std::string& key) {
  CHECK_RUNTIME(input_json.isMember(key), "Can not access json key: " + key);
  CHECK_RUNTIME(input_json[key].isObject() || input_json[key].isArray(),
      "Json key: " + key + " is of wrong type. Expected JSON object.");
  return input_json[key];
}
template<>
int32_t JsonUtils::getJsonValue<int32_t>(const Json& input_json, const std::string& key) {
  CHECK_RUNTIME(input_json.isMember(key), "Can not access json key: " + key);
  CHECK_RUNTIME(input_json[key].isInt(), "Json key: " + key + " is of wrong type. Expected int.");
  return input_json[key].asInt();
}
template<>
float JsonUtils::getJsonValue<float>(const Json& input_json, const std::string& key) {
  CHECK_RUNTIME(input_json.isMember(key), "Can not access json key: " + key);
  // There is no isFloat() method --> double is the native type, asFloat() casts
  CHECK_RUNTIME(input_json[key].isDouble(), "Json key: " + key + " is of wrong type. Expected float.");
  return input_json[key].asFloat();
}
template<>
double JsonUtils::getJsonValue<double>(const Json& input_json, const std::string& key) {
  CHECK_RUNTIME(input_json.isMember(key), "Can not access json key: " + key);
  CHECK_RUNTIME(input_json[key].isDouble(), "Json key: " + key + " is of wrong type. Expected double.");
  return input_json[key].asDouble();
}
template<>
std::string JsonUtils::getJsonValue<std::string>(const Json& input_json, const std::string& key) {
  CHECK_RUNTIME(input_json.isMember(key), "Can not access json key: " + key);
  CHECK_RUNTIME(input_json[key].isString(), "Json key: " + key + " is of wrong type. Expected string.");
  return input_json[key].asString();
}

// getJsonValue, OpenCV types
template<>
cv::Size JsonUtils::getJsonValue<cv::Size>(const Json& input_json, const std::string& key) {
  Json size_json = getJsonValue<Json>(input_json, key);
  CHECK_RUNTIME(size_json.size() == 2, "Json key: " + key + " has incorrect number of keys. Expected 2.");
  int32_t width = JsonUtils::getJsonValue<int32_t>(size_json, "width");
  int32_t height = JsonUtils::getJsonValue<int32_t>(size_json, "height");

  return cv::Size(width, height);
}
template<>
cv::Rect JsonUtils::getJsonValue<cv::Rect>(const Json& input_json, const std::string& key) {
  Json rect_json = getJsonValue<Json>(input_json, key);
  CHECK_RUNTIME(rect_json.size() == 4, "Json key: " + key + " has incorrect number of keys. Expected 4.");
  int32_t x = JsonUtils::getJsonValue<int32_t>(rect_json, "x");
  int32_t y = JsonUtils::getJsonValue<int32_t>(rect_json, "y");
  int32_t width = JsonUtils::getJsonValue<int32_t>(rect_json, "width");
  int32_t height = JsonUtils::getJsonValue<int32_t>(rect_json, "height");
  return cv::Rect(x, y, width, height);
}
template<>
cv::Rect2f JsonUtils::getJsonValue<cv::Rect2f>(const Json& input_json, const std::string& key) {
  Json rect_json = getJsonValue<Json>(input_json, key);
  CHECK_RUNTIME(rect_json.size() == 4, "Json key: " + key + " has incorrect number of keys. Expected 4.");
  float x = JsonUtils::getJsonValue<float>(rect_json, "x");
  float y = JsonUtils::getJsonValue<float>(rect_json, "y");
  float width = JsonUtils::getJsonValue<float>(rect_json, "width");
  float height = JsonUtils::getJsonValue<float>(rect_json, "height");
  return cv::Rect2f(x, y, width, height);
}

}  // namespace utils
}  // namespace bnr_data_product
