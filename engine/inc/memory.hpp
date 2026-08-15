#ifndef VGE_MEMORY_HPP
#define VGE_MEMORY_HPP

#include "common.hpp"
#include "logger.hpp"

namespace vge {

#define Malloc(size) internal_Malloc(size, __FILE__, __FUNCTION__, __LINE__)
#define Free(target) internal_Free(target, __FILE__, __FUNCTION__, __LINE__)

struct Memory : Singleton<Memory> {
  static void *internal_Malloc(size_t amount, const String &file,
                               const String &func, uint32 line);
  static void internal_Free(void *target, const String &file,
                            const String &func, uint32 line);

  static size_t LastAllocationSize();

  bool logMallocSizes = true;

private:
  size_t last;
};

} // namespace vge

#endif