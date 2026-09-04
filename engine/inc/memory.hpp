#ifndef VGE_MEMORY_HPP
#define VGE_MEMORY_HPP

#include "common.hpp"
#include "logger.hpp"

namespace vge {

#define Malloc(size) internal_Malloc(size, VGE_CALL_INFO)

#define Free() internal_Free(VGE_CALL_INFO)

struct Memory : Singleton<Memory> {
  bool logMallocSizes = true;
  bool logFreeSizes = true;

  static void IncreaseUsedMemory(size_t amount);
  static void DecreaseUsedMemory(size_t amount);

  static size_t GetUsedMemory();

private:
  size_t usedMemory;
};

enum MemoryState { UNALLOCATED = 0, ALLOCATED = 1, FREED = 2 };

template <typename T> struct Pointer {

  Pointer(const String &name = "Unnamed Pointer") { Initialize(name); }

  Pointer(const Pointer &ptr) {
    Initialize("Copy of " + ptr.name);

    CopyData(ptr.data, ptr.count);
  }

  ~Pointer() { internal_Free(VGE_CALL_INFO); }

  /**
   * @brief Allocates memory. Use the macro `Malloc` when calling.
   *
   * @param amount The amount of `typeSize` to allocate.
   * @param file The file this function was called in.
   * @param func The function this function was called in.
   * @param line The line this function was called on.
   *
   * @b Example:
   * @code{.cpp}

   Pointer<float> ptr;
   ptr.Malloc(3); // 3 floats allocated
   // then do whatever. access `data` with `ptr[...]` or `ptr.GetData()`

   // out of scope, the destructor is called automatically
   ptr.~Pointer();
   @endcode
   *
   * @return true Successful allocation.
   * @return false Unsuccessful allocation.
   */
  bool internal_Malloc(size_t amount, const String &file, const String &func,
                       uint32 line) {
    if (data) {
      Logger::internal_Log("You need to call Free first!", file, func, line);
      return false;
    }
    if (amount == 0) {
      Logger::internal_LogFatal("Cant allocate 0 bytes of memory!", file, func,
                                line);
      return false;
    }

    allocationSize = typeSize * amount;

    if (Memory::Get().logMallocSizes) {
      Logger::internal_Log("Attempting to allocate " +
                               ToString(allocationSize) +
                               " bytes of memory for Pointer \"" + name + "\".",
                           file, func, line);
    }

    data = (T *)std::malloc(allocationSize);
    if (!data) {
      if (Memory::Get().logMallocSizes) {
        Logger::internal_Log("Failed to allocate " + ToString(allocationSize) +
                                 " bytes of memory for Pointer \"" + name +
                                 "\"!",
                             file, func, line);
      }
      return false;
    }

    for (int i = 0; i < amount; i++) {
      new (&data[i]) T();
    }

    count = amount;

    Memory::IncreaseUsedMemory(allocationSize);

    mallocData = LogData(func, file, "", "", "", line);

    state = MemoryState::ALLOCATED;

    return true;
  }

  /**
   * @brief Frees the memory. Use the macro `Free` when calling.
   *
   * @param file The file this function was called in.
   * @param func The function this function was called in.
   * @param line The line this function was called on.
   */
  void internal_Free(const String &file, const String &func, uint32 line) {
    switch (state) {
    case UNALLOCATED:
      Logger::internal_Log(
          "You need to call Malloc first! State: UNALLOCATED (for Pointer \"" +
              name + "\")",
          file, func, line);
      return;
      break;
    case ALLOCATED:
      break;
    case FREED:
      Logger::internal_Log(
          "You need to call Malloc first! State: FREED (for Pointer \"" + name +
              "\")",
          file, func, line);
      return;
      break;
    default:
      Logger::internal_Log(
          "You need to call Malloc first! State: UNKNOWN (for Pointer \"" +
              name + "\")",
          file, func, line);
      return;
      break;
    }

    if (!data) {
      Logger::internal_Log("Data is not valid! (for Pointer \"" + name + "\")",
                           file, func, line);
      return;
    }

    for (int i = 0; i < count; i++) {
      data[i].~T();
    }

    if (Memory::Get().logFreeSizes) {
      Logger::internal_Log("Freeing " + ToString(allocationSize) +
                               " bytes of memory for Pointer \"" + name + "\"!",
                           file, func, line);
    }
    std::free(data);
    data = nullptr;

    Memory::DecreaseUsedMemory(allocationSize);

    state = MemoryState::FREED;

    allocationSize = 0;
    count = 0;
  }

  T *GetData() { return data; }

  T *GetData() const { return data; }

  void SetData(T *newData) { data = newData; }

  /**
   * @brief Get the amount of memory allocated in bytes.
   *
   * @return size_t
   */
  size_t GetAllocatedSize() const { return allocationSize; }

  // TODO: fix the way this is written (specifically the brief)
  /**
   * @brief Returns the number of `T` where allocated.

   * @return size_t The amount of `T` allocated.
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

  Pointer &operator=(const Pointer &other) {
    if (this == other)
      return this;
    if (other.state == UNALLOCATED) {
      Logger::LOG("other is UNALLOCATED! Cant copy!");
      return this;
    }
    if (other.state == FREED) {
      Logger::LOG("other is FREED! Cant copy!");
      this;
    }
    if (state == ALLOCATED) {
      Free();
    }

    Initialize("Copy of " + other.name);

    CopyData(other.data, other.count);

    return this;
  }

private:
  void Initialize(const String &name) {
    typeSize = sizeof(T);
    state = MemoryState::UNALLOCATED;
    data = nullptr;

    this->name = name;
  }
  void CopyData(const T *source, uint32 count) {
    Malloc(count);

    for (int i = 0; i < this->count; i++) {
      this->data[i] = source[i];
    }
  }

protected:
  String name;
  size_t count;
  size_t allocationSize = 0;
  size_t typeSize = 0;
  T *data = nullptr;
  MemoryState state;
  LogData mallocData;
};

} // namespace vge

#endif
