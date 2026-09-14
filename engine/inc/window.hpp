#ifndef VGE_WINDOW_HPP
#define VGE_WINDOW_HPP

#include "common.hpp"
#include "engine.hpp"
#include <SDL3/SDL.h>

namespace vge {
struct Window : Singleton<Window> {
  static void Init(String title = "VGE", uint width = 960, uint height = 640,
                   bool allowResize = true, bool fullscreen = false);
  //! `Window::Shutdown` is for internal use only! Use `Window::Stop` instead!
  static void Shutdown();
  static void Stop();
  static bool Process();
  static Vector2i GetDimensions();
  static void SwapBuffer();
  static SDL_Window *GetWindow();
  static void SetTitle(const String &title);
  static void CreatePopUp(const String &title, const String &content,
                          bool errorWindow = false);
  static float GetViewportAspect();

protected:
  SDL_Window *window;
  bool running;
  bool pillarboxed = false;
  Vector2i viewportSize = Vector2i();
  Vector2i viewportPosition = Vector2i();
};
} // namespace vge

#endif
