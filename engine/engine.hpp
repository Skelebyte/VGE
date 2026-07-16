#ifndef VGE_ENGINE_HPP
#define VGE_ENGINE_HPP

#include "common.hpp"
#include "logger.hpp"
#include <SDL3/SDL.h>

namespace vge {

struct Engine : Singleton<Engine> {
  static void init();
  /**
   * @brief Initializes the engine, window, and renderer.
   *
   * @param title
   * @param width
   * @param height
   * @param allowResize
   * @param fullscreen
   */
  static void fullInit(String title = "VGE", uint32 width = 600,
                       uint32 height = 400, bool allowResize = true,
                       bool fullscreen = false);
  static void shutdown();
  /**
   * @brief Shuts down the engine, window, and renderer.
   *
   */
  static void fullShutdown();
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