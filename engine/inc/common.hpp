#ifndef VGE_COMMON_HPP
#define VGE_COMMON_HPP

#include <cstdint>
#include <iostream>
#include <string>

#include "../ext/glad/gl.h"

namespace vge {

using uchar = unsigned char;
using uint8 = uint8_t;
using uint32 = uint32_t;
using uint64 = uint64_t;
using int32 = int32_t;
using int64 = int64_t;
using String = std::string;

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
  uint32 GetID() { return id; }

protected:
  uint32 *GetID_Ptr() { return &id; }
  void SetID(uint32 newID) { id = newID; }

private:
  uint32 id;
};

} // namespace vge

#endif