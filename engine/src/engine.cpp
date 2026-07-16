#include "../engine.hpp"
#include "../graphics.hpp"
#include "../window.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <cstddef>
#include <string>

using namespace vge;

void Engine::init() {
  Logger::init();

  if (isInit()) {
    Logger::LOG("Engine has already been initialized!");

    return;
  }

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    Logger::LOG("MEGA FUCKING FATAL!!!!");
    return;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  Time::init(SDL_GetTicks());

  setTargetFps(60);

  get().initialized = true;
}

void Engine::fullInit(String title, uint32 width, uint32 height,
                      bool allowResize, bool fullscreen) {
  init();
  Window::init(title, width, height, allowResize, fullscreen);
  Renderer::init();
}

void Engine::shutdown() {
  if (isInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return;
  }

  get().initialized = false;
}

void Engine::fullShutdown() {
  Renderer::shutdown();
  Window::close();
  Engine::shutdown();
}

void Engine::beginFrame() {
  get().isProcessFrame = false;
  Time::newFrame(SDL_GetTicks());

  get().processTime += Time::deltaTime();
  get().frameTime += Time::deltaTime();

  while (get().processTime >= get().targetFps) {
    get().processTime -= get().targetFps;
    get().isProcessFrame = true;

    if (get().frameTime >= 1.0f) {
      get().frameTime = 0.0f;
      get().fps = get().frames;
      get().frames = 0;
    }
  }

  if (get().isProcessFrame) {
    get().frames++;
  }
}

void Engine::endFrame() {
  if (!isInit()) {

    return;
  }
}

void Engine::setTargetFps(uint32 target) {
  if (target > 999) {
    get().targetFps = 1.0f / 999.0f;
  } else {
    get().targetFps = 1.0f / (float)target;
  }
}

uint32 Engine::getFps() { return get().fps; }
