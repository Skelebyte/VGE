#include "../logger.hpp"

using namespace vge;

void Logger::log(const String &msg, const String &file,
                 const String &function) {

  String logString = Time::getDateString() + ", " + Time::getTimeString() +
                     " | " + msg + " (" + file + ", " + function + ")";

  File::write(".log", logString);

  std::cout << logString << std::endl;
}