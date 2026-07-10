#ifndef VGE_TIME_HPP
#define VGE_TIME_HPP

#include "common.hpp"
#include <chrono>
#include <ctime>
#include <string>

namespace vge {

struct Time : Singleton<Time> {
  static void init(float tick);
  static void newFrame(float tick);

  static float deltaTime();
  static float unscaledDeltaTime();

  /**
   * @brief Get current date
   *
   * @return Current date in `YYYY-MM-DD` format.
   */
  static String getDateString();

  /**
   * @brief Get current time
   *
   * @return Current time in `HH:MM:SS AM/PM` format.
   */
  static String getTimeString();

private:
  float delta;
  float timeScale = 1.0f;
  float first;
  float last;
};

}; // namespace vge

#endif