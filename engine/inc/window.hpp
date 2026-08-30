#ifndef VGE_WINDOW_HPP
#define VGE_WINDOW_HPP

#include "common.hpp"
#include "engine.hpp"
#include "vector2i.hpp"
#include <SDL3/SDL.h>

namespace vge {
struct Window : Singleton<Window> {
  static void Init(String title = "VGE", uint32 width = 960,
                   uint32 height = 640, bool allowResize = true,
                   bool fullscreen = false);
  //! `Window::Shutdown` is for internal use only! Use `Window::Stop` instead!
  static void Shutdown();
  static void Stop();
  static bool Process();
  static Vector2I GetDimensions();
  static void SwapBuffer();
  static SDL_Window *GetWindow();
  static void SetTitle(const String &title);

protected:
  SDL_Window *window;
  bool running;
  bool pillarboxed = false;
  Vector2I viewportSize = Vector2I();
  Vector2I viewportPosition = Vector2I();
};
} // namespace vge

#endif