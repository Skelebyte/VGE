#include "../file.hpp"
#include "../memory.hpp"
#include <filesystem>

using namespace vge;

String File::read(const String &path) {
  if (File::exists(path) == false) {
    // THROW_ERROR(ERROR.Derived("", "File " + path + " does not exist!"));
    return "";
  }

  std::ifstream file;

  file.open(path, std::ios::binary | std::ios::ate);

  if (file.fail()) {
    // THROW_ERROR(ERROR.Derived("", "Failed to open file " + path + "."));
    return "";
  }

  std::streamsize size = (std::streamsize)file.tellg();
  file.seekg(0, std::ios::beg);

  // char *buffer = new char[size + 1];
  char *buffer = (char *)Memory::MALLOC(size + 1);
  if (!file.read(buffer, size)) {
    // THROW_ERROR(ERROR.Derived("", "Failed to read file " + path + "."));
    // delete[] buffer;
    Memory::free(buffer);
    return "";
  }

  buffer[size] = '\0';

  file.close();

  String data = buffer;
  // delete[] buffer;
  Memory::free(buffer);

  return data;
}

void File::write(const String &path, const String &content, bool overwrite) {
  std::ofstream file;

  if (overwrite) {
    file.open(path, std::ios::trunc);
  } else {
    file.open(path, std::ios::app);
  }

  file << content << std::endl;
  file.close();
}

bool File::exists(const String &path) { return std::filesystem::exists(path); }

size_t File::fileSize(const String &path) {
  return std::filesystem::file_size(path);
}

String File::getExtension(const String &path) {
  return ((std::filesystem::path)path).extension();
}