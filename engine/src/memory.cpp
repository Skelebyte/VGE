#include "../inc/memory.hpp"
#include <cstdlib>

using namespace vge;

void *Memory::internal_Malloc(size_t amount, const String &file,
                              const String &func, uint32 line) {
  Get().last = amount;

  if (Get().logMallocSizes) {
    Logger::internal_Log("Attempting to allocate " + ToString(amount) +
                             " bytes of memory.",
                         file, func, line);
  }

  return std::malloc(amount);
}

void Memory::internal_Free(void *target, const String &file, const String &func,
                           uint32 line) {
  if (target == nullptr) {
    Logger::internal_Log("Can't Free a nullptr!", file, func, line);
    return;
  }

  std::free(target);
}

size_t Memory::LastAllocationSize() { return Get().last; }