#define STB_IMAGE_IMPLEMENTATION
#include "../asset.hpp"

using namespace vge;

Asset::Asset(const String &path) { this->path = path; }

const String &Asset::getPath() const { return path; }

/* ------------ Texture ------------ */

Texture::Texture(const String &path, const TextureFilter &filter)
    : Asset(path) {
  if (path.empty() == true) {
    uchar *data = Texture::customTexture(4, 4, 255, 255, 255, 200, 200, 200);
    valid = true;
    loadFromData(data, 3, 4, 4);
    return;
  }

  if (File::exists(path) == false) {
    Logger::LOG("File \"" + path +
                "\" does not exist! Loading fallback texture.");
    textureFallback();
    return;
  }

  stbi_set_flip_vertically_on_load(1);

  int32 width, height, channels;

  uchar *data;

  data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (!data) {
    Logger::LOG("Failed to load texture \"" + path +
                "\". Loading fallback texture");
    textureFallback();
    return;
  }
  valid = true;
  loadFromData(data, channels, width, height, filter);
}

void Texture::textureFallback() {
  uchar *data = Texture::customTexture(4, 4, 255, 0, 255, 0, 0, 0);
  valid = false;
  loadFromData(data, 3, 4, 4);
}