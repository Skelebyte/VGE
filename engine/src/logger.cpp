#include "../inc/logger.hpp"
#include "../inc/memory.hpp"

using namespace vge;

void Logger::init() {
  if (File::exists(".log") == false)
    return;

  if (File::fileSize(".log") > 3 * 1024 * 1024) {
    Logger::log("Log cleared.", __FILE__, __FUNCTION__, true);
  }

  Logger::log("Logger initialized.", __FILE__, __FUNCTION__);
}

void Logger::log(const String &msg, const String &file, const String &function,
                 bool overwriteLog) {

  String logString = Time::getDateString() + ", " + Time::getTimeString() +
                     " | " + msg + " (" + file + ", " + function + ")";

  File::write(".log", logString, overwriteLog);

  std::cout << logString << std::endl;
}