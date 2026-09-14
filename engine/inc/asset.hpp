#ifndef VGE_ASSET_HPP
#define VGE_ASSET_HPP

#include "../ext/stb/stb_image.h"
#include "common.hpp"
#include "file.hpp"
#include "graphics.hpp"
#include "list.hpp"
#include "memory.hpp"

namespace vge {
struct Asset {
  Asset() = default;
  Asset(const String &path);

  const String &GetPath() const;

private:
  String path;
};

enum struct TextureFilter { LINEAR = 0, NEAREST = 1 };

struct Texture : public Asset, public ID {
  Texture(uint width, uint height, const Color &a, const Color &b,
          TextureFilter filter = TextureFilter::NEAREST);
  Texture(const String &path,
          const TextureFilter &filter = TextureFilter::NEAREST);
  ~Texture();
  static void CheckeredTextureData(Pointer<uchar> &data, uint width,
                                   uint height, const Color &a, const Color &b);
  void Bind();
  void Unbind();
  bool IsValid() const;

protected:
  void TextureFallback();
  void LoadFromData(Pointer<uchar> &data, uint channels, uint width,
                    uint height,
                    const TextureFilter &filter = TextureFilter::NEAREST);

private:
  bool valid;
};

struct Vertex {
  Vertex();
  Vertex(const Vector3f &pos, const Vector2f &uv, const Vector3f &norm);
  ~Vertex() = default;

  Vector3f position;
  Vector2f uv;
  Vector3f normal;
};

struct Mesh : Asset {
  Mesh() = default;
  Mesh(const String &path, bool blenderFix = true);
  ~Mesh() = default;

  static Mesh GeneratePlane(const Vector2f &dimensions = Vector2f(1.0f),
                            int divisions = 1);

  List<Vertex> vertices;
  List<uint> indices;

  List<float> data;
};

} // namespace vge

#endif
