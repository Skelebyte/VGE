#ifndef VGE_ENGINE_HPP
#define VGE_ENGINE_HPP

#include "common.hpp"
#include "logger.hpp"
#include <SDL3/SDL.h>

namespace vge {

struct Engine : Singleton<Engine> {
  static void init();
  static void shutdown();
  static void beginFrame();
  static void endFrame();
  static void setTargetFps(uint32 target);
  static uint32 getFps();

protected:
  bool isProcessFrame = false;
  float processTime;
  float frameTime;
  float targetFps;
  uint32 fps;
  uint32 frames;
};

} // namespace vge

#endif