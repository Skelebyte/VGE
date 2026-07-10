#ifndef VGE_GRAPHICS_HPP
#define VGE_GRAPHICS_HPP

#include "common.hpp"
#include "engine.hpp"
#include "window.hpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>

namespace vge {

struct Color {
  float r, g, b, a;

  Color(float rgb = 1.0f, float alpha = 1.0f);
  Color(float red, float green, float blue, float alpha = 1.0f);

  static Color White();
  static Color Black();
  static Color Red();
  static Color Green();
  static Color Blue();
  static Color Magenta();
  static Color Grey();

  /**
   * @brief Get RGBA as an array pointer. Needs to be freed manually.
   *
   * @return float*
   */
  float *asArrayPtr();
};

struct Renderer : Singleton<Renderer> {
  static void init();
  static void shutdown();
  // static void ToggleWireframe();

private:
  SDL_GLContext gl;
  bool wireframe;
};

} // namespace vge

#endif