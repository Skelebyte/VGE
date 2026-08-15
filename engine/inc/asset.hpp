#ifndef VGE_ASSET_HPP
#define VGE_ASSET_HPP

#include "../ext/stb/stb_image.h"
#include "common.hpp"
#include "file.hpp"
#include "memory.hpp"

namespace vge {
struct Asset {
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

struct Mesh : Asset {
  Mesh(const String &path);
};

} // namespace vge

#endif