#ifndef VGE_ASSET_HPP
#define VGE_ASSET_HPP

#include "common.hpp"
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

struct Texture : Asset {
  Texture(const String &path);
  void bind();
  void unbind();

protected:
  void textureFallback();

private:
  uint32 id;
};

} // namespace vge

#endif