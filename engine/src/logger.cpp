#include "../inc/logger.hpp"
#include "../inc/memory.hpp"
#include "../inc/window.hpp"
#include <cassert>
#include <cstdlib>

using namespace vge;

LogData::LogData(const String &func, const String &file, const String &msg,
                 const String &time, const String &date, uint32 line) {
  this->function = func;
  this->file = file;
  this->message = msg;
  this->time = time;
  this->date = date;
  this->lineNumber = line;
}

String LogData::GetFunction() const { return function; }
String LogData::GetFile() const { return file; }
String LogData::GetMessage() const { return message; }
String LogData::GetTime() const { return time; }
String LogData::GetDate() const { return date; }
uint32 LogData::GetLineNumber() const { return lineNumber; }

bool Logger::print = true;
LogData Logger::lastLog = LogData();

void Logger::Init() {
  if (File::Exists(".log") == false)
    return;

  if (File::FileSize(".log") > File::MbToBytes(3)) {
    Logger::internal_Log("Log cleared.", __FILE__, __FUNCTION__, __LINE__,
                         true);
  }

  Logger::internal_Log("Logger initialized. Log size: " +
                           ToString(File::BytesToMb(File::FileSize(".log"))) +
                           "mb.",
                       __FILE__, __FUNCTION__, __LINE__);
}

void Logger::internal_Log(const String &msg, const String &file,
                          const String &function, uint32 lineNumber,
                          bool overwriteLog, LogType logType) {

  String type = "";
  switch (logType) {
  case LogType::STANDARD:
    type = "";
    break;
  case LogType::FATAL:
    type = " FATAL ";
    break;
  case LogType::ASSERT:
    type = " ASSERT ";
    break;
  default:
    type = "";
    break;
  }

  String logString = Time::GetDateString() + ", " + Time::GetTimeString() +
                     " [ from: " + file + ":" + ToString(lineNumber) + ", " +
                     function + "() ] " + type + " | " + msg;

  File::Write(".log", logString, overwriteLog);

  std::cout << logString << std::endl;

  lastLog = LogData(function, file, msg, Time::GetTimeString(),
                    Time::GetDateString(), lineNumber);
}

void Logger::internal_LogFatal(const String &msg, const String &file,
                               const String &function, uint32 lineNumber) {
  internal_Log(msg, file, function, lineNumber, false, LogType::FATAL);

  Window::CreatePopUp("Fatal Error",
                      msg + "\n\nfrom: " + file + ":" + ToString(lineNumber) +
                          ", " + function + "()",
                      true);

  exit(EXIT_FAILURE);
}

void Logger::internal_CheckOpenGLError(const String &msg, const String &file,
                                       const String &function,
                                       uint32 lineNumber) {
  uint32 glErr = glGetError();

  if (glErr != GL_NO_ERROR) {
    internal_LogFatal(msg + "\n OpenGL error: " + ToString(glErr) + ".", file,
                      function, lineNumber);
  }
}

void Logger::internal_Assert(bool condition, const String &msg,
                             VGE_CALL_PARAMS) {
  if (condition == false) {
    internal_Log(msg, VGE_CALL_PARAMS_USAGE, false, LogType::ASSERT);
    Window::CreatePopUp("Assert Failed!",
                        msg + "\n\nfrom: " + file + ":" + ToString(line) +
                            ", " + func + "()",
                        true);
    exit(EXIT_FAILURE);
  }
}

const LogData &Logger::GetLastLog() { return lastLog; }
