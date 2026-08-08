#ifndef VGE_GRAPHICS_HPP
#define VGE_GRAPHICS_HPP

#include "common.hpp"
#include "engine.hpp"
#include "matrix4.hpp"
#include "memory.hpp"
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

struct Uniform : public ID {
  Uniform(const String &name, uint32 shaderID);
  const String &getName() const;

  void setValue(const Matrix4 &value);
  void setValue(const Vector3 &value);
  void setValue(const Color &value);
  void setValue(float value);
  void setValue(int32 value);
  void setValue(bool value);

protected:
  String name;
};

struct VBO : public ID {
  VBO(float *verts, size_t size);
  ~VBO();

  void bind();
  void unbind();
};

struct VAO : public ID {
  VAO();
  ~VAO();

  void bind();
  void unbind();
  void linkAttrib(VBO &vbo, uint32 layout, uint32 components, uint32 type,
                  size_t stride, void *offset);
};

struct EBO : public ID {
  EBO(uint32 *indices, size_t size);
  ~EBO();

  void bind();
  void unbind();
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