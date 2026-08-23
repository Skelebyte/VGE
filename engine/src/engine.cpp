#include "../inc/engine.hpp"
#include "../inc/graphics.hpp"
#include "../inc/window.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <chrono>
#include <cstddef>
#include <string>

using namespace vge;

void Engine::Init(String title, uint32 width, uint32 height, bool allowResize,
                  bool fullscreen) {
  Logger::Init();

  if (IsInit()) {
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

  Time::Init(SDL_GetTicks());

  SetTargetFps(60);

  Get().initialized = true;
  Window::Init(title, width, height, allowResize, fullscreen);
  Renderer::Init();

  Get().engineStartTime = std::chrono::system_clock::now().time_since_epoch() /
                          std::chrono::milliseconds(1);
}

void Engine::Shutdown() {
  if (IsInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return;
  }

  Renderer::Shutdown();
  Window::Shutdown();

  Logger::LOG("Engine shutting down. Uptime: " + ToString(GetUptime() / 1000) +
              "s.");

  Get().initialized = false;
}

bool Engine::Process() {
  if (IsInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return false;
  }
  return true;
}

void Engine::BeginFrame() {
  Get().isProcessFrame = false;
  Time::NewFrame(SDL_GetTicks());

  Get().processTime += Time::DeltaTime();
  Get().frameTime += Time::DeltaTime();

  while (Get().processTime >= Get().targetFps) {
    Get().processTime -= Get().targetFps;
    Get().isProcessFrame = true;

    if (Get().frameTime >= 1.0f) {
      Get().frameTime = 0.0f;
      Get().fps = Get().frames;
      Get().frames = 0;
    }
  }

  if (Get().isProcessFrame) {
    Get().frames++;
  }
}

void Engine::EndFrame() {
  if (!IsInit()) {

    return;
  }
}

void Engine::SetTargetFps(uint32 target) {
  if (target > 999) {
    Get().targetFps = 1.0f / 999.0f;
  } else {
    Get().targetFps = 1.0f / (float)target;
  }
}

uint32 Engine::GetFps() { return Get().fps; }

uint64 Engine::GetUptime() {
  return (std::chrono::system_clock::now().time_since_epoch() /
          std::chrono::milliseconds(1)) -
         Get().engineStartTime;
}
