#include "../graphics.hpp"
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
  float *arr = (float *)malloc(sizeof(float) * 4);

  arr[0] = r;
  arr[1] = g;
  arr[2] = b;
  arr[3] = a;

  return arr;
}

/* ------------ Uniform ------------ */

Uniform::Uniform(const String &name, uint32 shaderID) {
  id = glGetUniformLocation(shaderID, name.c_str());
  // TODO: add opengl error check

  this->name = name;
}

const String &Uniform::getName() const { return name; }

uint32 Uniform::getID() const { return id; }

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