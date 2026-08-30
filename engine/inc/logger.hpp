#ifndef VGE_LOGGER_HPP
#define VGE_LOGGER_HPP

#include "common.hpp"
#include "file.hpp"
#include "time.hpp"

namespace vge {

struct LogData {
  LogData() = default;
  LogData(const String &func, const String &file, const String &msg,
          const String &time, const String &date, uint32 line);
  ~LogData() = default;

  String GetFunction() const;
  String GetFile() const;
  String GetMessage() const;
  String GetTime() const;
  String GetDate() const;
  uint32 GetLineNumber() const;

private:
  String function;
  String file;
  String message;
  String time;
  String date;
  uint32 lineNumber;
};

struct Logger : Singleton<Logger> {
  static void Init();
  static void internal_Log(const String &msg, const String &file = __FILE__,
                           const String &function = "__FUNCTION__",
                           const uint32 lineNumber = 0,
                           bool overwriteLog = false, bool fatal = false);
  static void internal_LogFatal(const String &msg,
                                const String &file = __FILE__,
                                const String &function = "__FUNCTION__",
                                const uint32 lineNumber = 0);
  static void internal_CheckOpenGLError(const String &msg,
                                        const String &file = __FILE__,
                                        const String &function = "__FUNCTION__",
                                        const uint32 lineNumber = 0);

  static const LogData &GetLastLog();

  static bool print;

protected:
  static LogData lastLog;
};

#define LOG(msg) internal_Log(msg, __FILE__, __FUNCTION__, __LINE__)
#define LOG_FATAL(msg) internal_LogFatal(msg, __FILE__, __FUNCTION__, __LINE__)

/*
 * Something to note with this macro, im subtracting linesAbove from
 * __LINE__ to hopefully point directly to the
 * function that failed, as this macro should be under each opengl function
 * called.
 */
#define CHECK_OPENGL(msg, linesAbove)                                          \
  internal_CheckOpenGLError(msg, __FILE__, __FUNCTION__, __LINE__ - linesAbove)

} // namespace vge

#endif