#include "../inc/logger.hpp"
#include "../inc/memory.hpp"
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
                          bool overwriteLog) {

  String logString = Time::GetDateString() + ", " + Time::GetTimeString() +
                     " [ from: " + file + ":" + ToString(lineNumber) + ", " +
                     function +
                     "() ]"
                     " | " +
                     msg;

  File::Write(".log", logString, overwriteLog);

  std::cout << logString << std::endl;

  lastLog = LogData(function, file, msg, Time::GetTimeString(),
                    Time::GetDateString(), lineNumber);
}

void Logger::internal_LogFatal(const String &msg, const String &file,
                               const String &function, uint32 lineNumber) {
  internal_Log(msg, file, function, lineNumber);

  // TODO: popup window

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

const LogData &Logger::GetLastLog() { return lastLog; }