#pragma once

#include <string>
#include <ostream>

namespace bnr_data_product {
namespace logging {

enum LogLevel {VERBOSE, INFO, WARNING, ERROR, NONE};

// Logging Class --> should not ever be used directly.
// Use the wrappers below
class Logging {
 public:
  // The main methods
  void setLogLevel(LogLevel logLevel);
  std::ostream& log(LogLevel logLevel);
  std::ostream& logIf(LogLevel logLevel, bool condition);
  // Singleton
  static Logging& getLogger();
  Logging(Logging const&) = delete;
  void operator=(Logging const&) = delete;

 private:
  // CURRENTLY SET TO ALLOW ALL LOGGING BY DEFAULT
  LogLevel logLevel__{VERBOSE};

  Logging(){}
};

//
// Inline wrappers for Logging class
//
// Set the log level
inline void setLogLevel(LogLevel logLevel) {
  Logging::getLogger().setLogLevel(logLevel);
}

// Log
inline std::ostream& log(LogLevel logLevel) {
  return Logging::getLogger().log(logLevel);
}

// Log if the condition is true
inline std::ostream& logIf(LogLevel logLevel, bool condition) {
  return Logging::getLogger().logIf(logLevel, condition);
}

}  // namespace logging
}  // namespace bnr_data_product

using namespace bnr_data_product::logging;  // NOLINT

