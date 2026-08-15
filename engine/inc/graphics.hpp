#ifndef VGE_GRAPHICS_HPP
#define VGE_GRAPHICS_HPP

#include "common.hpp"
#include "engine.hpp"
#include "list.hpp"
#include "matrix4.hpp"
#include "memory.hpp"
#include "vector3.hpp"
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
   * @brief Get RGBA as a pointer. Needs to be freed manually.
   *
   * @return float*
   */
  float *AsPtr();
};

struct Uniform : public ID {
  Uniform(const String &name, uint32 shaderID);
  const String &GetName() const;

  void SetValue(const Matrix4 &value);
  void SetValue(const Vector3 &value);
  void SetValue(const Color &value);
  void SetValue(float value);
  void SetValue(int32 value);
  void SetValue(bool value);

protected:
  String name;
};

struct Shader : public ID {
  Shader(const String &name, const String &fragPath, const String &vertPath);
  ~Shader();
  void AddUniform(const String &name);
  Uniform *GetUniform(const String &name);
  void Bind();
  void SetName(const String &name);
  String &GetName();

protected:
  String name;
  List<Uniform> uniforms;
  bool IsCompileOk(uint32 shader, const String &type);
  bool IsLinkOk();
};

struct VBO : public ID {
  VBO(float *verts, size_t size);
  ~VBO();

  void Bind();
  void Unbind();
};

struct VAO : public ID {
  VAO();
  ~VAO();

  void Bind();
  void Unbind();
  void LinkAttrib(VBO &vbo, uint32 layout, uint32 components, uint32 type,
                  size_t stride, void *offset);
};

struct EBO : public ID {
  EBO(uint32 *indices, size_t size);
  ~EBO();

  void Bind();
  void Unbind();
};

struct Renderer : Singleton<Renderer> {
  static void Init();
  static void Shutdown();
  static void UpdateCamera(const Vector3 &pos, const Vector3 &rot,
                           float fovDeg = 75.0f);
  // static void ToggleWireframe();

private:
  SDL_GLContext gl;
  bool wireframe;
};

} // namespace vge

#endif