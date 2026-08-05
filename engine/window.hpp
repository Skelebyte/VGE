#ifndef VGE_WINDOW_HPP
#define VGE_WINDOW_HPP

#include "common.hpp"
#include "engine.hpp"
#include "vector2.hpp"
#include <SDL3/SDL.h>

namespace vge {
struct Window : Singleton<Window> {
  static void init(String title = "VGE", uint32 width = 960,
                   uint32 height = 640, bool allowResize = true,
                   bool fullscreen = false);
  static void close();
  static bool process();
  static Vector2 getDimensions();
  static void swapBuffer();
  static SDL_Window *getWindow();

protected:
  SDL_Window *window;
  bool running;
  bool pillarboxed = false;
  Vector2 viewportSize = Vector2();
  Vector2 viewportPosition = Vector2();
};
} // namespace vge

#endif