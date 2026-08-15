#ifndef VGE_WINDOW_HPP
#define VGE_WINDOW_HPP

#include "common.hpp"
#include "engine.hpp"
#include "vector2.hpp"
#include <SDL3/SDL.h>

namespace vge {
struct Window : Singleton<Window> {
  static void Init(String title = "VGE", uint32 width = 960,
                   uint32 height = 640, bool allowResize = true,
                   bool fullscreen = false);
  static void Close();
  static bool Process();
  static Vector2 GetDimensions();
  static void SwapBuffer();
  static SDL_Window *GetWindow();
  static void SetTitle(const String &title);

protected:
  SDL_Window *window;
  bool running;
  bool pillarboxed = false;
  Vector2 viewportSize = Vector2();
  Vector2 viewportPosition = Vector2();
};
} // namespace vge

#endif