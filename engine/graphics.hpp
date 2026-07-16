#ifndef VGE_GRAPHICS_HPP
#define VGE_GRAPHICS_HPP

#include "common.hpp"
#include "engine.hpp"
#include "matrix4.hpp"
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

struct Uniform {
  Uniform(const String &name, uint32 shaderID);
  const String &getName() const;
  uint32 getID() const;

  void setValue(const Matrix4 &value);
  void setValue(const Vector3 &value);
  void setValue(const Color &value);
  void setValue(float value);
  void setValue(int32 value);
  void setValue(bool value);

protected:
  String name;
  uint32 id;
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