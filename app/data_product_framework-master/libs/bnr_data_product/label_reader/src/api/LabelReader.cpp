#include "bnr_data_product/LabelReader.hpp"

#include <memory>
#include <string>
#include <vector>

#include "bnr_data_product/api/LabelReaderPri.hpp"
#include "bnr_data_product/utils/ParamsReader.hpp"

namespace bnr {
namespace data_product {

LabelReader::LabelReader(const std::string& paramsJson) {
  bnr_data_product::utils::ParamsReader params_reader(paramsJson);
  LabelReaderPri::Params label_reader_params = params_reader.run<LabelReaderPri::Params>();
  label_reader_pri_ = std::make_shared<LabelReaderPri>(label_reader_params);
}

bnr::data_product::ReadSymbol LabelReader::run(
    const cv::Mat& label_img) const
  { return label_reader_pri_->run(label_img); }

}  // namespace data_product
}  // namespace bnr
