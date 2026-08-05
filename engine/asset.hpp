#ifndef VGE_ASSET_HPP
#define VGE_ASSET_HPP

#include "common.hpp"
#include "ext/stb/stb_image.h"
#include "file.hpp"
#include "memory.hpp"

namespace vge {
struct Asset {
  Asset(const String &path);
  static Asset load(const String &path);

  const String &getPath() const;

private:
  String path;
};

enum TextureFilter { LINEAR = 0, NEAREST = 1 };

struct Texture : Asset {
  Texture(const String &path,
          const TextureFilter &filter = TextureFilter::NEAREST);
  static uchar *customTexture(uint32 width, uint32 height, uint32 r1, uint32 g1,
                              uint32 b1, uint32 r2, uint32 g2, uint32 b2);
  void bind();
  void unbind();
  bool isValid() const;

protected:
  void textureFallback();
  void loadFromData(uchar *data, uint32 channels, uint32 w, uint32 height,
                    const TextureFilter &filter = TextureFilter::NEAREST);

private:
  uint32 id;
  bool valid;
};

} // namespace vge

#endif