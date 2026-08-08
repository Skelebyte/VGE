#include "../inc/graphics.hpp"
#include <SDL3/SDL_video.h>
#include <cstdlib>

using namespace vge;

Color::Color(float rgb, float alpha) {
  r = rgb;
  g = rgb;
  b = rgb;
  a = alpha;
}

Color::Color(float red, float green, float blue, float alpha) {
  r = red;
  g = green;
  b = blue;
  a = alpha;
}

Color Color::White() { return Color(1.0f); }
Color Color::Black() { return Color(0.0f); }
Color Color::Red() { return Color(1.0f, 0.0f, 0.0f); }
Color Color::Green() { return Color(0.0f, 1.0f, 0.0f); }
Color Color::Blue() { return Color(0.0f, 0.0f, 1.0f); }
Color Color::Magenta() { return Color(1.0f, 0.0f, 1.0f); }
Color Color::Grey() { return Color(0.5f, 0.5f, 0.5f); }

float *Color::asArrayPtr() {
  float *arr = (float *)Memory::MALLOC(sizeof(float) * 4);

  arr[0] = r;
  arr[1] = g;
  arr[2] = b;
  arr[3] = a;

  return arr;
}

/* ------------ Uniform ------------ */

Uniform::Uniform(const String &name, uint32 shaderID) {
  setID(glGetUniformLocation(shaderID, name.c_str()));
  // TODO: add opengl error check

  this->name = name;
}

const String &Uniform::getName() const { return name; }

/* ------------ VBO ------------ */

// TODO: add error checking
VBO::VBO(float *verts, size_t size) {
  glGenBuffers(1, getID_Ptr());
  // THROW_ERROR_GL(FATAL.Derived("GL_GEN_BUFFERS_FAIL",
  //                              "Generating the VBO buffer failed!"));

  glBindBuffer(GL_ARRAY_BUFFER, getID());
  // THROW_ERROR_GL(FATAL.Derived("GL_BIND_BUFFER_FAIL",
  //                              "Binding VBO failed (Constructor)!"));

  glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
  // THROW_ERROR_GL(FATAL.Derived("GL_BUFFER_DATA_FAIL",
  //                              "Assigning data to the VBO failed!"));
}

VBO::~VBO() { glDeleteBuffers(1, getID_Ptr()); }

// TODO: add error checking
void VBO::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, getID());
  // THROW_ERROR_GL(FATAL.Derived("GL_BIND_BUFFER_FAIL", "Binding VBO
  // failed!"));
}

void VBO::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

/* ------------ VAO ------------ */

// TODO: add error checking
VAO::VAO() {
  glGenVertexArrays(1, getID_Ptr());
  // THROW_ERROR_GL(FATAL.Derived("GL_GEN_VERTEX_ARRAYS_FAIL",
  //                              "Generating the VAO buffer failed!"));
}

VAO::~VAO() { glDeleteVertexArrays(1, getID_Ptr()); }

// TODO: add error checking
void VAO::bind() {
  glBindVertexArray(getID());
  // THROW_ERROR_GL(FATAL.Derived("GL_BIND_VERTEX_ARRAY_FAIL",
  //                              "Binding the VAO buffer failed!"));
}

void VAO::unbind() { glBindVertexArray(0); }

// TODO: add error checking
void VAO::linkAttrib(VBO &vbo, uint32 layout, uint32 components, uint32 type,
                     size_t stride, void *offset) {
  vbo.bind();
  glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
  // THROW_ERROR_GL(FATAL.Derived("GL_VERTEX_ATTRIB_POINTER_FAIL"));

  glEnableVertexAttribArray(layout);
  // THROW_ERROR_GL(FATAL.Derived("GL_ENABLE_VERTEX_ATTRIB_ARRAY_FAIL"));

  vbo.unbind();
}

/* ------------ EBO ------------ */

// TODO: add error checking
EBO::EBO(uint32 *indices, size_t size) {
  glGenBuffers(1, getID_Ptr());
  // THROW_ERROR_GL(FATAL.Derived("GL_GEN_BUFFERS_FAIL",
  //                              "Generating the EBO buffer failed!"));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getID());
  // THROW_ERROR_GL(
  //     FATAL.Derived("GL_BIND_BUFFER_FAIL", "Binding the EBO buffer
  //     failed!"));

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  // THROW_ERROR_GL(FATAL.Derived("GL_BUFFER_DATA_FAIL",
  //                              "Assigning data to the EBO buffer failed!"));
}

EBO::~EBO() { glDeleteBuffers(1, getID_Ptr()); }

void EBO::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getID()); }

void EBO::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

/* ------------ Renderer ------------ */

void Renderer::init() {
  if (Engine::isInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return;
  }
  if (isInit()) {
    return;
  }

  get().gl = SDL_GL_CreateContext(Window::getWindow());
  if (get().gl == nullptr) {
    Logger::LOG("Failed to create OpenGL context! SDL error: " +
                toString(*SDL_GetError()));
    return;
  }

  SDL_GL_MakeCurrent(Window::getWindow(), get().gl);

  if (gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0) {
    Logger::LOG("Failed to initialize glad! Remind me to come back here to add "
                "a get error function :)");
    return;
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  get().initialized = true;
}

void Renderer::shutdown() {
  if (isInit() == false)
    return;

  SDL_GL_DestroyContext(get().gl);

  get().initialized = false;
}