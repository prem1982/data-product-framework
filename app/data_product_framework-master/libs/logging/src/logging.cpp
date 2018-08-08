#include "logging.hpp"

#include <iostream>

namespace bnr_data_product {
namespace logging {

std::ostream logNullStream(nullptr);

void Logging::setLogLevel(LogLevel logLevel) {
  logLevel__ = logLevel;
}

std::ostream& Logging::log(LogLevel logLevel) {
  if (logLevel < logLevel__) {
    return logNullStream;
  }

  return (logLevel == ERROR) ? std::cerr : std::cout;
}

std::ostream& Logging::logIf(LogLevel logLevel, bool condition) {
  return (condition) ? log(logLevel) : logNullStream;
}

Logging& Logging::getLogger() {
  static Logging instance;
  return instance;
}

}  // namespace logging
}  // namespace bnr_data_product

