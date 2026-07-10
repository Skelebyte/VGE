#ifndef VGE_LOGGER_HPP
#define VGE_LOGGER_HPP

#include "common.hpp"
#include "file.hpp"
#include "time.hpp"

namespace vge {

struct Logger : Singleton<Logger> {
  static void log(const String &msg, const String &file = __FILE__,
                  const String &function = "__FUNCTION__");

protected:
  bool print;
};

#define LOG(msg) log(msg, __FILE__, __FUNCTION__)

} // namespace vge

#endif