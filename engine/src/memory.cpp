#include "../inc/memory.hpp"
#include <cstdlib>

using namespace vge;

void *Memory::malloc(size_t amount) {
  get().last = amount;
  return std::malloc(amount);
}

void Memory::free(void *target) {
  if (target == nullptr) {
    // TODO: throw error
    return;
  }

  std::free(target);
}

size_t Memory::lastAllocationSize() { return get().last; }