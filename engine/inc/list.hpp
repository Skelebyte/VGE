#ifndef VGE_LIST_HPP
#define VGE_LIST_HPP

#include "common.hpp"
#include "logger.hpp"
#include <vector>

namespace vge {
template <typename T> struct List {
  List() { data = std::vector<T>(); }
  /**
   * @brief Returns number of elements
   *
   * @return uint32
   */
  uint32 Size() { return data.size(); }
  void Add(const T &value, bool first = false) {
    if (first) {
      data.insert(data.begin(), value);
    } else {
      data.push_back(value);
    }
  }

  void Remove(uint32 index) {
    if (index > Size()) {
      // err::ErrorSystem::THROW_ERROR(err::ERROR.Derived(
      //     "INDEX_OUT_OF_BOUNDS", "Index " + std::to_string(index) +
      //                                " is out of bounds. Size of list: " +
      //                                std::to_string(Size()) + "."));
      return;
    }

    data.erase(data.begin() + index);
  }

  void RemoveElement(T element) {
    for (uint32 i = 0; i < Size(); i++) {
      if (data[i] == element) {
        Remove(i);
        break;
      }
    }
  }

  void Clear() { data.clear(); }

  T *AsPtr() { return data.data(); }

  std::vector<T> *AsVector() { return &data; }

  T *operator[](uint32 index) {
    if (index >= Size()) {
      Logger::LOG("Index " + ToString(index) +
                  " is out of bounds (list size: " + ToString(Size()) + ").");

      return nullptr;
    }

    return &data[index];
  }

private:
  std::vector<T> data;
};
} // namespace vge

#endif