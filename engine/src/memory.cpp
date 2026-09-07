#include "../inc/memory.hpp"
#include <cstdlib>

using namespace vge;

void Memory::IncreaseUsedMemory(size_t amount) { Get().usedMemory += amount; }

void Memory::DecreaseUsedMemory(size_t amount) { Get().usedMemory -= amount; }

size_t Memory::GetUsedMemory() { return Get().usedMemory; }
