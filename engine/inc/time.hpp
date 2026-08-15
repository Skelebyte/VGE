#ifndef VGE_TIME_HPP
#define VGE_TIME_HPP

#include "common.hpp"
#include <chrono>
#include <ctime>
#include <string>

namespace vge {

struct Time : Singleton<Time> {
  static void Init(float tick);
  static void NewFrame(float tick);

  static float DeltaTime();
  static float UnscaledDeltaTime();

  /**
   * @brief Get current date
   *
   * @return Current date in `YYYY-MM-DD` format.
   */
  static String GetDateString();

  /**
   * @brief Get current time
   *
   * @return Current time in `HH:MM:SS` format.
   */
  static String GetTimeString();

private:
  float delta;
  float timeScale = 1.0f;
  float first;
  float last;
};

}; // namespace vge

#endif