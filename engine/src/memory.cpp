#include "../inc/memory.hpp"
#include <cstdlib>

using namespace vge;

// void *Memory::internal_Malloc(size_t amount, const String &file,
//                               const String &func, uint32 line) {
//   Get().last = amount;

//   if (Get().logMallocSizes) {
//     Logger::internal_Log("Attempting to allocate " + ToString(amount) +
//                              " bytes of memory.",
//                          file, func, line);
//   }

//   return std::malloc(amount);
// }

// template <typename T>
// Pointer<T> Memory::internal_MallocPtr(size_t amount, const String &file,
//                                       const String &func, uint32 line) {
//   Get().last = amount;

//   if (Get().logMallocSizes) {
//     Logger::internal_Log("Attempting to allocate " + ToString(amount) +
//                              " bytes of memory.",
//                          file, func, line);
//   }

//   return Pointer<T>(std::malloc(amount), amount);
// }

// void Memory::internal_Free(void *target, const String &file, const String
// &func,
//                            uint32 line) {
//   if (target == nullptr) {
//     Logger::internal_Log("Can't free a nullptr!", file, func, line);
//     return;
//   }

//   if (Get().logFreeSizes) {
//     Logger::internal_Log("Attempting to free " + ToString(sizeof(target)) +
//                              " bytes of memory.",
//                          file, func, line);
//   }

//   std::free(target);
// }

// template <typename T>
// void Memory::internal_FreePtr(Pointer<T> &ptr, const String &file,
//                               const String &func, uint32 line) {
//   if (Get().logFreeSizes) {
//     Logger::internal_Log("Attempting to free " + ToString(ptr.GetSize()) +
//                              " bytes of memory.",
//                          file, func, line);
//   }

//   std::free(ptr.data);
// }

// size_t Memory::LastAllocationSize() { return Get().last; }