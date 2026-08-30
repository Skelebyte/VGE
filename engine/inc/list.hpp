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

  void internal_Remove(uint32 index, VGE_CALL_PARAMS) {
    if (index > Size()) {
      Logger::internal_LogFatal(
          "Index " + ToString(index) +
              " is out of bounds (list size: " + ToString(Size()) + ").",
          VGE_CALL_PARAMS_USAGE);
      return;
    }

    data.erase(data.begin() + index);
  }

  void internal_RemoveElement(T element, VGE_CALL_PARAMS) {
    for (uint32 i = 0; i < Size(); i++) {
      if (data[i] == element) {
        internal_Remove(i);
        break;
      }
    }
  }

  void Clear() { data.clear(); }

  T *AsPtr() { return data.data(); }

  std::vector<T> *AsVector() { return &data; }

  T &operator[](uint32 index) {
    if (index >= Size()) {
      Logger::LOG_FATAL("Index " + ToString(index) +
                        " is out of bounds (list size: " + ToString(Size()) +
                        ").");
    }

    return data[index];
  }

private:
  std::vector<T> data;
};
} // namespace vge

#endif