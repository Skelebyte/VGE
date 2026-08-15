#ifndef VGE_FILE_HPP
#define VGE_FILE_HPP

#include "common.hpp"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace vge {

struct File {
  static String Read(const String &path);
  static void Write(const String &path, const String &content,
                    bool overwrite = false);
  static bool Exists(const String &path);
  static size_t FileSize(const String &path);
  static String GetExtension(const String &path);

  static size_t MbToBytes(uint32 mb);
  static double BytesToMb(size_t bytes);
};

} // namespace vge

#endif