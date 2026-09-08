#ifndef VGE_ENGINE_HPP
#define VGE_ENGINE_HPP

#include "common.hpp"
#include "logger.hpp"
#include <SDL3/SDL.h>

namespace vge {

struct Engine : Singleton<Engine> {
  /**
   * @brief Initializes the engine, window, and renderer.
   *
   * @param title
   * @param width
   * @param height
   * @param allowResize
   * @param fullscreen
   */
  static void Init(String title = "VGE", uint width = 960, uint height = 640,
                   bool allowResize = true, bool fullscreen = false);
  /**
   * @brief Shuts down the engine, window, and renderer.
   *
   */
  static void Shutdown();
  static bool Process();
  static void BeginFrame();
  static void EndFrame();
  static void SetTargetFps(uint target);
  static uint GetFps();
  static uint64 GetUptimeMs();

protected:
  bool isProcessFrame = false;
  float processTime;
  float frameTime;
  float targetFps;
  uint fps;
  uint frames;
  uint64 engineStartTime;
};

} // namespace vge

#endif
