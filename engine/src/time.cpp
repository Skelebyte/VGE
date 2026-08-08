#include "../inc/time.hpp"
#include "../inc/logger.hpp"

using namespace vge;

void Time::init(float tick) {
  if (isInit()) {
    Logger::LOG("Time has already been initialized!");

    return;
  }

  get().last = tick / 1000.0f;

  get().initialized = true;
}

void Time::newFrame(float tick) {
  if (!isInit()) {
    Logger::LOG("Time must be initialized!");

    return;
  }

  get().first = tick / 1000.0f;

  get().delta = get().first - get().last;

  get().last = get().first;
}

float Time::deltaTime() { return get().delta * get().timeScale; }

float Time::unscaledDeltaTime() { return get().delta; }

String Time::getDateString() {
  time_t time = std::time(nullptr);
  tm *currentTime = localtime(&time);

  int day = currentTime->tm_mday;
  int month = currentTime->tm_mon + 1;
  int year = currentTime->tm_year + 1900;

  return (std::to_string(year) + "-" + std::to_string(month) + "-" +
          std::to_string(day));
}

String Time::getTimeString() {
  time_t time = std::time(nullptr);
  tm *currentTime = localtime(&time);

  String AMOrPM;
  int hour = currentTime->tm_hour;

  if (hour > 12) {
    AMOrPM = " PM";
    hour -= 12;
  } else {
    AMOrPM = " AM";
  }

  int minute = currentTime->tm_min;
  int second = currentTime->tm_sec;

  return (std::to_string(hour) + ":" + std::to_string(minute) + ":" +
          std::to_string(second) + AMOrPM);
}