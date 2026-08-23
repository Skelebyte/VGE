#include "../inc/file.hpp"
#include "../inc/memory.hpp"
#include <filesystem>

using namespace vge;

String File::Read(const String &path) {
  if (File::Exists(path) == false) {
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
  Pointer<char> buffer = Pointer<char>();
  buffer.Malloc(size + 1);
  if (!file.read(buffer.GetData(), size)) {
    // THROW_ERROR(ERROR.Derived("", "Failed to read file " + path + "."));
    // delete[] buffer;
    //? buffer.Free(); // im not sure about commenting this out, im pretty sure
    //? the Pointer destructor will handle it though.
    return "";
  }

  buffer[size] = '\0';

  file.close();

  String data = buffer.GetData();
  // delete[] buffer;

  return data;
}

void File::Write(const String &path, const String &content, bool overwrite) {
  std::ofstream file;

  if (overwrite) {
    file.open(path, std::ios::trunc);
  } else {
    file.open(path, std::ios::app);
  }

  file << content << std::endl;
  file.close();
}

bool File::Exists(const String &path) { return std::filesystem::exists(path); }

size_t File::FileSize(const String &path) {
  return std::filesystem::file_size(path);
}

String File::GetExtension(const String &path) {
  return ((std::filesystem::path)path).extension();
}

size_t File::MbToBytes(uint32 mb) { return mb * 1024 * 1024; }

double File::BytesToMb(size_t bytes) { return (double)bytes / 1024 / 1024; }