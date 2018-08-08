#include "bnr_data_product/label_reader/PriceReaderPostProcessor.hpp"

#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "bnr_data_product/label_reader/definitions.hpp"

using bnr::data_product::label_reader::PriceReaderPostProcessor;
using bnr::data_product::ReadSymbol;

PriceReaderPostProcessor reader_post_processor_ = PriceReaderPostProcessor();

static const char expected_price_1[] = "";
static const char expected_price_2[] = "3.42";
static const char expected_price_3[] = "13.42";
static const char expected_price_4[] = "0.11";
static const char expected_price_5[] = "0.88";
static const char expected_price_6[] = "1.34";

TEST(PriceDetectorPostProcessor, invalidPriceWithPeriodAtBeginning) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("3", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("4", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("2", cv::Rect(0, 0, 0, 40), 1.0f));

  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_1, result_price);
}

TEST(PriceDetectorPostProcessor, validPriceWithDollarMisinterpreted) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 10), 1.0f));
  read_sym_vec.push_back(ReadSymbol("3", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0 , 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("4", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("2", cv::Rect(0, 0, 0, 40), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_2, result_price);
}

TEST(PriceDetectorPostProcessor, validPriceThreeDigits) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("3", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("4", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("2", cv::Rect(0, 0, 0, 40), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_2, result_price);
}

TEST(PriceDetectorPostProcessor, validPriceFourDigits) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("3", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("4", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("2", cv::Rect(0, 0, 0, 40), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_3, result_price);
}

TEST(PriceDetectorPostProcessor, validPriceThreeDigitsWithDollar) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("$", cv::Rect(0, 0, 0, 10), 1.0f));
  read_sym_vec.push_back(ReadSymbol("3", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("4", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("2", cv::Rect(0, 0, 0, 40), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_2, result_price);
}

TEST(PriceDetectorPostProcessor, invalidPriceWithPeriodAtThree) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("3", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("4", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("2", cv::Rect(0, 0, 0, 40), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_1, result_price);
}

TEST(PriceDetectorPostProcessor, invalidPriceWithPeriodAtFour) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("3", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("4", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("2", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_1, result_price);
}

TEST(PriceDetectorPostProcessor, emptyInput) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_1, result_price);
}

TEST(PriceDetectorPostProcessor, priceWithTwoPeriods) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_1, result_price);
}

TEST(PriceDetectorPostProcessor, priceWithThreeDigitsWithoutPeriod) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_4, result_price);
}

TEST(PriceDetectorPostProcessor, validCentPrice) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("8", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("8", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("c", cv::Rect(0, 0, 0, 10), 1.0f));
  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_5, result_price);
}

TEST(PriceDetectorPostProcessor, priceWithCentValueMoreThanTwoDigits) {
  std::vector<bnr::data_product::ReadSymbol> read_sym_vec;
  read_sym_vec.push_back(ReadSymbol("1", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol(".", cv::Rect(0, 0, 0, 5), 1.0f));
  read_sym_vec.push_back(ReadSymbol("3", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("4", cv::Rect(0, 0, 0, 40), 1.0f));
  read_sym_vec.push_back(ReadSymbol("2", cv::Rect(0, 0, 0, 40), 1.0f));

  const std::string result_price = reader_post_processor_.run(read_sym_vec);
  ASSERT_EQ(expected_price_6, result_price);
}
