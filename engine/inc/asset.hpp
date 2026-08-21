#ifndef VGE_ASSET_HPP
#define VGE_ASSET_HPP

#include "../ext/stb/stb_image.h"
#include "common.hpp"
#include "file.hpp"
#include "list.hpp"
#include "memory.hpp"
#include "vector2.hpp"
#include "vector3.hpp"

namespace vge {
struct Asset {
  Asset() = default;
  Asset(const String &path);

  const String &GetPath() const;

private:
  String path;
};

enum TextureFilter { LINEAR = 0, NEAREST = 1 };

struct Texture : public Asset, public ID {
  Texture(const String &path,
          const TextureFilter &filter = TextureFilter::NEAREST);
  ~Texture();
  static uchar *CustomTexture(uint32 width, uint32 height, uint32 r1, uint32 g1,
                              uint32 b1, uint32 r2, uint32 g2, uint32 b2);
  void Bind();
  void Unbind();
  bool IsValid() const;

protected:
  void TextureFallback();
  void LoadFromData(uchar *data, uint32 channels, uint32 width, uint32 height,
                    const TextureFilter &filter = TextureFilter::NEAREST);

private:
  bool valid;
};

struct Vertex {
  Vertex();
  Vertex(Vector3 pos, Vector2 uv, Vector3 norm);
  ~Vertex() = default;

  Vector3 position;
  Vector2 uv;
  Vector3 normal;
};

struct Mesh : Asset {
  Mesh() = default;
  Mesh(const String &path, bool blenderFix = true);
  ~Mesh() = default;

  static Mesh GeneratePlane(uint32 divisions, const Vector2 &dimensions);

  List<Vertex> vertices;
  List<uint32> indices;

  List<float> data;
};

} // namespace vge

#endif