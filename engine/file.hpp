#ifndef VGE_FILE_HPP
#define VGE_FILE_HPP

#include "common.hpp"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace vge {

struct File {
  static String read(const String &path);
  static void write(const String &path, const String &content,
                    bool overwrite = false);
  static bool exists(const String &path);
};

} // namespace vge

#endif