#include "../logger.hpp"
#include "../memory.hpp"

using namespace vge;

void Logger::init() {
  if (File::exists("game.log") == false)
    return;

  if (File::fileSize("game.log") > 3 * 1024 * 1024) {
    Logger::log("Log cleared.", __FILE__, __FUNCTION__, true);
  }
}

void Logger::log(const String &msg, const String &file, const String &function,
                 bool overwriteLog) {

  String logString = Time::getDateString() + ", " + Time::getTimeString() +
                     " | " + msg + " (" + file + ", " + function + ")";

  File::write(".log", logString, overwriteLog);

  std::cout << logString << std::endl;
}