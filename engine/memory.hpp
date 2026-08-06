#ifndef VGE_MEMORY_HPP
#define VGE_MEMORY_HPP

#include "common.hpp"
#include "logger.hpp"

namespace vge {

struct Memory : Singleton<Memory> {
  //! Use the macro! Example: `Memory::MALLOC(sizeof(float) * 4);`
  static void *malloc(size_t amount);
  static void free(void *target);

  static size_t lastAllocationSize();

private:
  size_t last;
};

#define MALLOC(amount)                                                         \
  malloc(amount);                                                              \
  Logger::LOG("Allocating " + toString(amount) + " bytes of memory.")

} // namespace vge

#endif