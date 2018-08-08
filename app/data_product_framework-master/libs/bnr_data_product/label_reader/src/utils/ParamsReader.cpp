#include "bnr_data_product/utils/ParamsReader.hpp"

#include <string>

#include "utils/JsonUtils.hpp"

namespace bnr_data_product {
namespace utils {

using namespace bnr::data_product::label_reader; // NOLINT
using bnr_data_product::io::Json;
using bnr_data_product::utils::JsonUtils;

template<>
PriceDetectorPreProcessor::Params ParamsReader::run<PriceDetectorPreProcessor::Params>(
    const Json& pre_processor_json) {
  int32_t adaptive_thresh_blocksize = JsonUtils::getJsonValue<int32_t>(
      pre_processor_json, "adaptive_thresh_blocksize");
  int32_t adaptive_thresh_mean_value = JsonUtils::getJsonValue<int32_t>(
      pre_processor_json, "adaptive_thresh_mean_value");

  const PriceDetectorPreProcessor::Params pre_processor_params(
      adaptive_thresh_blocksize, adaptive_thresh_mean_value);
  return pre_processor_params;
}

template<>
MserDoer::Params ParamsReader::run<MserDoer::Params>(const Json& mser_doer_json) {
  cv::Size open_kernel_size = JsonUtils::getJsonValue<cv::Size>(mser_doer_json, "open_kernel_size");
  cv::Size close_kernel_size = JsonUtils::getJsonValue<cv::Size>(mser_doer_json, "close_kernel_size");
  cv::Size mop_kernel_size = JsonUtils::getJsonValue<cv::Size>(mser_doer_json, "mop_kernel_size");
  cv::Size erode_kernel_size = JsonUtils::getJsonValue<cv::Size>(mser_doer_json, "erode_kernel_size");
  int32_t delta = JsonUtils::getJsonValue<int32_t>(mser_doer_json, "delta");
  int32_t min_area = JsonUtils::getJsonValue<int32_t>(mser_doer_json, "min_area");
  int32_t max_area = JsonUtils::getJsonValue<int32_t>(mser_doer_json, "max_area");
  double max_variation = JsonUtils::getJsonValue<double>(mser_doer_json, "max_variation");
  double min_diversity = JsonUtils::getJsonValue<double>(mser_doer_json, "min_diversity");
  int32_t group_threshold = JsonUtils::getJsonValue<int32_t>(mser_doer_json, "group_threshold");
  double group_epsilon = JsonUtils::getJsonValue<double>(mser_doer_json, "group_epsilon");

  const MserDoer::Params mser_doer_params(
      open_kernel_size, close_kernel_size, mop_kernel_size, erode_kernel_size, delta,
      min_area, max_area, max_variation, min_diversity, group_threshold, group_epsilon);
  return mser_doer_params;
}

template<>
PriceDetectorPostProcessor::Params ParamsReader::run<PriceDetectorPostProcessor::Params>(
    const Json& post_processor_json) {
  int32_t min_area = JsonUtils::getJsonValue<int32_t>(post_processor_json, "min_area");
  int32_t max_area = JsonUtils::getJsonValue<int32_t>(post_processor_json, "max_area");
  int32_t height_thresh = JsonUtils::getJsonValue<int32_t>(post_processor_json, "height_thresh");
  int32_t distance_thresh = JsonUtils::getJsonValue<int32_t>(post_processor_json, "distance_thresh");
  int32_t y_thresh = JsonUtils::getJsonValue<int32_t>(post_processor_json, "y_thresh");
  float min_aspect = JsonUtils::getJsonValue<float>(post_processor_json, "min_aspect");
  float max_aspect = JsonUtils::getJsonValue<float>(post_processor_json, "max_aspect");
  int32_t img_buffer = JsonUtils::getJsonValue<int32_t>(post_processor_json, "img_buffer");
  int32_t group_threshold = JsonUtils::getJsonValue<int32_t>(post_processor_json, "group_threshold");
  double group_epsilon = JsonUtils::getJsonValue<double>(post_processor_json, "group_epsilon");

  const PriceDetectorPostProcessor::Params post_processor_params(
      min_area, max_area, height_thresh, distance_thresh, y_thresh, min_aspect, max_aspect,
      img_buffer, group_threshold, group_epsilon);
  return post_processor_params;
}

template<>
PriceDetector::Params ParamsReader::run<PriceDetector::Params>(const Json& price_detector_json) {
  // Parse PriceDetectorPreProcessor::Params
  const Json pre_processor_json = JsonUtils::getJsonValue<Json>(price_detector_json, "PreProcessorParams");
  const auto pre_processor_params = run<PriceDetectorPreProcessor::Params>(pre_processor_json);

  // Parse MserDoer::Params
  const Json mser_doer_json = JsonUtils::getJsonValue<Json>(price_detector_json, "MserDoerParams");
  const auto mser_doer_params = run<MserDoer::Params>(mser_doer_json);

  // Parse PriceDetectorPostProcessor::Params
  const Json post_processor_json = JsonUtils::getJsonValue<Json>(price_detector_json, "PostProcessorParams");
  const auto post_processor_params = run<PriceDetectorPostProcessor::Params>(post_processor_json);

  // Create the PriceDetector::Params and return
  const PriceDetector::Params price_detector_params(
      pre_processor_params, mser_doer_params, post_processor_params);
  return price_detector_params;
}

template<>
PriceReaderPreProcessor::Params ParamsReader::run<PriceReaderPreProcessor::Params>(
    const Json& pre_processor_json) {
  float denoising_h = JsonUtils::getJsonValue<float>(pre_processor_json, "denoising_h");
  int32_t denoising_templateWindowSize = JsonUtils::getJsonValue<int32_t>(
      pre_processor_json, "denoising_templateWindowSize");
  int32_t denoising_searchWindowSize = JsonUtils::getJsonValue<int32_t>(
      pre_processor_json, "denoising_searchWindowSize");

  const PriceReaderPreProcessor::Params pre_processor_params(
      denoising_h, denoising_templateWindowSize, denoising_searchWindowSize);
  return pre_processor_params;
}

template<>
PriceReader::Params ParamsReader::run<PriceReader::Params>(const Json& price_reader_json) {
  // Parse PriceReaderPreProcessor::Params
  const Json pre_processor_json = JsonUtils::getJsonValue<Json>(price_reader_json, "PreProcessorParams");
  const auto pre_processor_params = run<PriceReaderPreProcessor::Params>(pre_processor_json);

  // Create the PriceReader::Params and return
  const PriceReader::Params price_reader_params(
      pre_processor_params);
  return price_reader_params;
}

template<>
bnr::data_product::LabelReaderPri::Params ParamsReader::run<
    bnr::data_product::LabelReaderPri::Params>(const Json& input_json) {
  const Json label_reader_json = JsonUtils::getJsonValue<Json>(input_json, "LabelReaderParams");

  const float scale_factor = JsonUtils::getJsonValue<float>(label_reader_json, "scale_factor");

  const cv::Rect2f nominal_patch = JsonUtils::getJsonValue<cv::Rect2f>(label_reader_json, "nominal_patch");

  const Json price_detector_json = JsonUtils::getJsonValue<Json>(label_reader_json, "PriceDetectorParams");
  const auto& price_detector_params = run<PriceDetector::Params>(price_detector_json);

  const Json price_reader_json = JsonUtils::getJsonValue<Json>(label_reader_json, "PriceReaderParams");
  const auto& price_reader_params = run<PriceReader::Params>(price_reader_json);

  const bnr::data_product::LabelReaderPri::Params label_reader_params(scale_factor, nominal_patch,
      price_detector_params, price_reader_params);
  return label_reader_params;
}

template<>
bnr::data_product::LabelReaderPri::Params ParamsReader::run<
    bnr::data_product::LabelReaderPri::Params>() {
  return run<bnr::data_product::LabelReaderPri::Params>(params_);
}

}  // namespace utils
}  // namespace bnr_data_product
