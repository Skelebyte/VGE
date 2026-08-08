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
  uint32 size() { return data.size(); }
  void Add(const T &value, bool first = false) {
    if (first) {
      data.insert(data.begin(), value);
    } else {
      data.push_back(value);
    }
  }

  void remove(uint32 index) {
    if (index > size()) {
      // err::ErrorSystem::THROW_ERROR(err::ERROR.Derived(
      //     "INDEX_OUT_OF_BOUNDS", "Index " + std::to_string(index) +
      //                                " is out of bounds. Size of list: " +
      //                                std::to_string(Size()) + "."));
      return;
    }

    data.erase(data.begin() + index);
  }

  void removeElement(T element) {
    for (uint32 i = 0; i < size(); i++) {
      if (data[i] == element) {
        remove(i);
        break;
      }
    }
  }

  void clear() { data.clear(); }

  T *pointer() { return data.data(); }

  std::vector<T> *Vector() { return &data; }

  T &operator[](uint32 index) {
    if (index >= size()) {
      // err::ErrorSystem::THROW_ERROR(err::FATAL.Derived(
      //     "INDEX_OUT_OF_BOUNDS", "Index " + std::to_string(index) +
      //                                " is out of bounds. Size of list: " +
      //                                std::to_string(Size()) + "."));
      // return nullptr;
    }

    return data[index];
  }

private:
  std::vector<T> data;
};
} // namespace vge

#endif