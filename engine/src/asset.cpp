#include "../asset.hpp"

using namespace vge;

Asset::Asset(const String &path) { this->path = path; }

const String &Asset::getPath() const { return path; }

Texture::Texture(const String &path) : Asset(path) {
  if (path.empty() == true) {
    uchar *data = Texture::CustomTexture(4, 4, 255, 255, 255, 200, 200, 200);
    isValid = true;
    LoadFromData(data, 3, 4, 4);
    return;
  }

  if (File::exists(path) == false) {
    // THROW_ERROR(WARNING.Derived(
    //     "", "File " + path + " does not exist! Loading missing texture."));

    textureFallback();
    return;
  }

  stbi_set_flip_vertically_on_load(1);

  int32 width, height, channels;

  uchar *data;

  data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (!data) {
    // THROW_ERROR(WARNING.Derived("", "Failed to load texture " + path +
    //                                     ". Loading missing texture."));
    textureFallback();
    return;
  }
  isValid = true;
  LoadFromData(data, channels, width, height, filter);
}

void Texture::textureFallback() {
  uchar *data = Texture::CustomTexture(4, 4, 255, 0, 255, 0, 0, 0);
  isValid = false;
  LoadFromData(data, 3, 4, 4);
}