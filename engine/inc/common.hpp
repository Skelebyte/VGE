#ifndef VGE_COMMON_HPP
#define VGE_COMMON_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../ext/glad/gl.h"

namespace vge {

// template <typename T> using Vector = std::vector<T>;

using uchar = unsigned char;
using uint8 = uint8_t;
// using uint = uint32_t; // USE uint
using uint64 = uint64_t;
// using int = int32_t; // USE int
using int64 = int64_t;
using String = std::string;

/**
 * @def VGE_CALL_INFO
 * its bogus
 */
#define VGE_CALL_INFO __FILE__, __FUNCTION__, __LINE__
#define VGE_CALL_PARAMS const String &file, const String &func, const uint line
#define VGE_CALL_PARAMS_USAGE file, func, line

//! this is not great... should stick to SCREAMING_SNAKE_CASE for macros
#define ToString(value) std::to_string(value)

template <typename T> struct Singleton {
  // Singleton(const Singleton &) = delete;

  static T &Get() {
    static T instance;
    return instance;
  }
  static bool IsInit() { return Get().initialized; }

protected:
  bool initialized = false;
};

struct ID {
  uint GetID() { return id; }

protected:
  uint *GetID_Ptr() { return &id; }
  void SetID(uint newID) { id = newID; }

private:
  uint id;
};

} // namespace vge

#endif
