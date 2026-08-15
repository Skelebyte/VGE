#include "../inc/time.hpp"
#include "../inc/logger.hpp"

using namespace vge;

void Time::Init(float tick) {
  if (IsInit()) {
    Logger::LOG("Time has already been initialized!");

    return;
  }

  Get().last = tick / 1000.0f;

  Get().initialized = true;
}

void Time::NewFrame(float tick) {
  if (!IsInit()) {
    Logger::LOG("Time must be initialized!");

    return;
  }

  Get().first = tick / 1000.0f;

  Get().delta = Get().first - Get().last;

  Get().last = Get().first;
}

float Time::DeltaTime() { return Get().delta * Get().timeScale; }

float Time::UnscaledDeltaTime() { return Get().delta; }

String Time::GetDateString() {
  time_t time = std::time(nullptr);
  tm *currentTime = localtime(&time);

  int day = currentTime->tm_mday;
  int month = currentTime->tm_mon + 1;
  int year = currentTime->tm_year + 1900;

  return (ToString(year) + "-" + ToString(month) + "-" + ToString(day));
}

String Time::GetTimeString() {
  time_t time = std::time(nullptr);
  tm *currentTime = localtime(&time);

  String AMOrPM;
  int hour = currentTime->tm_hour;

  int minute = currentTime->tm_min;
  int second = currentTime->tm_sec;

  return ((hour < 10 ? "0" : "") + ToString(hour) + ":" +
          (minute < 10 ? "0" : "") + ToString(minute) + ":" +
          (second < 10 ? "0" : "") + ToString(second));
}