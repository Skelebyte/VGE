#ifndef VGE_MEMORY_HPP
#define VGE_MEMORY_HPP

#include "common.hpp"
#include "logger.hpp"

namespace vge {

#define Malloc(size) internal_Malloc(size, VGE_CALL_INFO)

#define Free() internal_Free(VGE_CALL_INFO)

// #define MallocPtr(type, amount) \
//    internal_MallocPtr<type>(sizeof(type) * amount, __FILE__, __FUNCTION__, \
//                             __LINE__)
//  #define FreePtr(type, ptr) \
//    internal_FreePtr<type>(ptr, __FILE__, __FUNCTION__, __LINE__)

struct Memory : Singleton<Memory> {
  // static void *internal_Malloc(size_t amount, const String &file,
  //                              const String &func, uint32 line);
  // template <typename T>
  // static Pointer<T> internal_MallocPtr(size_t amount, const String &file,
  //                                      const String &func, uint32 line);
  // static void internal_Free(void *target, const String &file,
  //                           const String &func, uint32 line);
  // template <typename T>
  // static void internal_FreePtr(Pointer<T> &ptr, const String &file,
  //                              const String &func, uint32 line);

  // static size_t LastAllocationSize();

  bool logMallocSizes = true;
  bool logFreeSizes = true;

  static void IncreaseUsedMemory(size_t amount);
  static void DecreaseUsedMemory(size_t amount);

  static size_t GetUsedMemory();

private:
  size_t usedMemory;
  size_t last;
};

template <typename T> struct Pointer {
  Pointer() { typeSize = sizeof(T); }
  ~Pointer() { internal_Free(VGE_CALL_INFO); }

  bool internal_Malloc(size_t size, const String &file, const String &func,
                       uint32 line) {
    if (data) {
      Logger::internal_Log("You need to call Free first!", file, func, line);
      return false;
    }

    allocationSize = typeSize * size;

    Logger::internal_Log("Attempting to allocate " + ToString(allocationSize) +
                             " bytes of memory.",
                         file, func, line);

    data = (T *)std::malloc(allocationSize);
    if (!data) {
      Logger::internal_Log("Failed to allocate " + ToString(allocationSize) +
                               " bytes of memory!",
                           file, func, line);
      return false;
    }

    for (int i = 0; i < size; i++) {
      new (&data[i]) T();
    }

    count = size;

    Memory::IncreaseUsedMemory(allocationSize);

    return true;
  }

  void internal_Free(const String &file, const String &func, uint32 line) {
    if (!data) {
      Logger::internal_Log("You need to call Malloc first!", file, func, line);
      return;
    }

    for (int i = 0; i < count; i++) {
      data[i].~T();
    }

    Logger::internal_Log("Freeing " + ToString(allocationSize) +
                             " bytes of memory.",
                         file, func, line);
    std::free(data);
    data = nullptr;

    Memory::DecreaseUsedMemory(allocationSize);

    allocationSize = 0;
    count = 0;
  }

  T *GetData() { return data; }
  T *GetData() const { return data; }

  void SetData(T *newData) { data = newData; }

  size_t GetAllocatedSize() const { return allocationSize; }

  // TODO: fix the way this is written (specifically the brief)
  /**
   * @brief Returns how the number of `T` where allocated.
   * @example If this was a plain `malloc` call (`malloc(sizeof(float) * 3);`)
   * it would return `3`.
   * @return size_t
   */
  size_t GetAmountAllocated() const { return count; }

  T &operator[](int i) {
    if (i < 0)
      return data[0];
    if (i > count)
      return data[0];

    return data[i];
  }

  T &operator[](int i) const {
    if (i < 0)
      return data[0];
    if (i > count)
      return data[0];

    return data[i];
  }

  bool operator!() { return !data; }

protected:
  size_t count;
  size_t allocationSize = 0;
  size_t typeSize = 0;
  T *data = nullptr;
};

} // namespace vge

#endif