#pragma once

#include <string>

#include "opencv2/core.hpp"

#include "io/Json.hpp"
#include "utils/ParamsReader.hpp"

#include "bnr_data_product/api/LabelReaderPri.hpp"

namespace bnr_data_product {
namespace utils {

// Parsing for LabelReader
template<>
bnr::data_product::LabelReaderPri::Params
    ParamsReader::run<bnr::data_product::LabelReaderPri::Params>();

// Parsing for PriceDetector
template<>
bnr::data_product::label_reader::PriceDetector::Params
    ParamsReader::run<bnr::data_product::label_reader::PriceDetector::Params>(
    const bnr_data_product::io::Json& price_detector_json);
template<>
bnr::data_product::label_reader::PriceDetectorPreProcessor::Params
    ParamsReader::run<bnr::data_product::label_reader::PriceDetectorPreProcessor::Params>(
    const bnr_data_product::io::Json& pre_processor_json);
template<>
bnr::data_product::label_reader::MserDoer::Params
    ParamsReader::run<bnr::data_product::label_reader::MserDoer::Params>(
    const bnr_data_product::io::Json& mser_doer_json);
template<>
bnr::data_product::label_reader::PriceDetectorPostProcessor::Params
    ParamsReader::run<bnr::data_product::label_reader::PriceDetectorPostProcessor::Params>(
    const bnr_data_product::io::Json& post_processor_json);

// Parsing for PriceReader
template<>
bnr::data_product::label_reader::PriceReader::Params
    ParamsReader::run<bnr::data_product::label_reader::PriceReader::Params>(
    const bnr_data_product::io::Json& price_reader_json);
template<>
bnr::data_product::label_reader::PriceReaderPreProcessor::Params
    ParamsReader::run<bnr::data_product::label_reader::PriceReaderPreProcessor::Params>(
    const bnr_data_product::io::Json& pre_processor_json);

}  // namespace utils
}  // namespace bnr_data_product
