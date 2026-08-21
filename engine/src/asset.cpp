#define STB_IMAGE_IMPLEMENTATION
#include "../inc/asset.hpp"

using namespace vge;

Asset::Asset(const String &path) { this->path = path; }

const String &Asset::GetPath() const { return path; }

/* ------------ Texture ------------ */

Texture::Texture(const String &path, const TextureFilter &filter)
    : Asset(path) {
  if (path.empty() == true) {
    uchar *data = Texture::CustomTexture(4, 4, 255, 255, 255, 200, 200, 200);
    valid = true;
    LoadFromData(data, 3, 4, 4);
    return;
  }

  if (File::Exists(path) == false) {
    Logger::LOG("File \"" + path +
                "\" does not exist! Loading fallback texture.");
    TextureFallback();
    return;
  }

  stbi_set_flip_vertically_on_load(1);

  int32 width, height, channels;

  uchar *data;

  // TODO: log how much memory is being allocated here (if possible)
  data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (!data) {
    Logger::LOG("Failed to load texture \"" + path +
                "\". Loading fallback texture");
    TextureFallback();
    return;
  }
  valid = true;
  LoadFromData(data, channels, width, height, filter);
}

Texture::~Texture() { glDeleteTextures(1, GetID_Ptr()); }

uchar *Texture::CustomTexture(uint32 width, uint32 height, uint32 r1, uint32 g1,
                              uint32 b1, uint32 r2, uint32 g2, uint32 b2) {
  uchar *data = (uchar *)Memory::Malloc(width * height * 3);
  for (int32 y = 0; y < height; y++) {
    for (int32 x = 0; x < width; x++) {
      float t = (float)x / width;
      float s = (float)y / height;

      int32 index = (y * width + x) * 3;
      if (((int32)(s * height) + (int32)(t * width)) % 2 == 0) {
        data[index] = r1;
        data[index + 1] = g1;
        data[index + 2] = b1;
      } else {
        data[index] = r2;
        data[index + 1] = g2;
        data[index + 2] = b2;
      }
    }
  }

  return data;
}

void Texture::Bind() { glBindTexture(GL_TEXTURE_2D, GetID()); }

void Texture::Unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

bool Texture::IsValid() const { return valid; }

void Texture::TextureFallback() {
  uchar *data = Texture::CustomTexture(4, 4, 255, 0, 255, 0, 0, 0);
  valid = false;
  LoadFromData(data, 3, 4, 4);
}

// TODO: add error checking
void Texture::LoadFromData(uchar *data, uint32 channels, uint32 width,
                           uint32 height, const TextureFilter &filter) {
  if (!data) {
    // THROW_ERROR(ERROR.Derived("", "The `data` parameter is not valid!"));
    return;
  }

  glGenTextures(1, GetID_Ptr());
  // THROW_ERROR_GL(FATAL.Derived("", "Failed to generate texture."));

  glBindTexture(GL_TEXTURE_2D, GetID());
  // THROW_ERROR_GL(FATAL.Derived("", "Failed to bind texture."));

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // THROW_ERROR_GL(
  //     FATAL.Derived("", "Setting GL_TEXTURE_WRAP_S parameter failed."));

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // THROW_ERROR_GL(
  //     FATAL.Derived("", " Setting GL_TEXTURE_WRAP_T parameter failed."));

  if (filter == NEAREST) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // THROW_ERROR_GL(FATAL.Derived("", "Setting MIN_FILTER failed."));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // THROW_ERROR_GL(FATAL.Derived("", "Setting MAG_FILTER failed."));
  } else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // THROW_ERROR_GL(FATAL.Derived("", "Setting MIN_FILTER failed."));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // THROW_ERROR_GL(FATAL.Derived("", "Setting MAG_FILTER failed."));
  }

  uint32 format = channels == 4 ? GL_RGBA : GL_RGB;

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  // THROW_ERROR_GL(FATAL.Derived("", "Failed to set texture data."));

  glGenerateMipmap(GL_TEXTURE_2D);
  // THROW_ERROR_GL(FATAL.Derived("", "Failed to generate mipmap."));

  Memory::Free(data);
}

/* ------------ Vertex ------------ */

Vertex::Vertex() {
  position = Vector3();
  uv = Vector2();
  normal = Vector3();
}

Vertex::Vertex(Vector3 pos, Vector2 uv, Vector3 norm) {
  position = pos;
  this->uv = uv;
  normal = norm;
}

/* ------------ Mesh ------------ */

Mesh Mesh::GeneratePlane(uint32 divisions, const Vector2 &dimensions) {
  Vector2 planeDimensions;

  if (divisions == 0)
    divisions = 1;

  if (dimensions == Vector2(0.0f)) {
    planeDimensions = Vector2(1.0f);
  } else {
    planeDimensions = dimensions;
  }

  Mesh mesh;

  float triangleSideX = planeDimensions.x / divisions;
  float triangleSideY = planeDimensions.y / divisions;

  for (uint32 row = 0; row <= divisions;
       row++) { // possibly may need to use divisions + 1
    for (uint32 col = 0; col <= divisions;
         col++) { // possibly may need to use divisions + 1

      if (row < divisions && col < divisions) {
        uint32 index = row * (divisions + 1) + col;

        // top triangle
        mesh.indices.Add(index);
        mesh.indices.Add(index + 1);
        mesh.indices.Add(index + (divisions + 1));

        // bottom triangle
        mesh.indices.Add(index + 1);
        mesh.indices.Add(index + (divisions + 1) + 1);
        mesh.indices.Add(index + (divisions + 1));
      }

      Vector3 pos = Vector3((col * triangleSideX) - dimensions.x / 2, 0.0f,
                            (row * -triangleSideY) + dimensions.y / 2);
      Vector2 uv = Vector2((float)col / divisions, (float)row / divisions);
      Vector3 normal = Vector3(0, 1, 0);
      mesh.vertices.Add(Vertex(pos, uv, normal));

      mesh.data.Add(pos.x);
      mesh.data.Add(pos.y);
      mesh.data.Add(pos.z);
      mesh.data.Add(uv.x);
      mesh.data.Add(uv.y);
      mesh.data.Add(normal.x);
      mesh.data.Add(normal.y);
      mesh.data.Add(normal.z);
    }
  }

  return mesh;
}