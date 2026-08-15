#include "../inc/window.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>

using namespace vge;

void Window::Init(String title, uint32 width, uint32 height, bool allowResize,
                  bool fullscreen) {
  if (Engine::IsInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return;
  }
  if (IsInit() || Get().window != nullptr) {
    return;
  }

  uint32 flags = SDL_WINDOW_OPENGL;
  if (allowResize) {
    flags |= SDL_WINDOW_RESIZABLE;
  }
  if (fullscreen) {
    flags |= SDL_WINDOW_FULLSCREEN;
  }

  Get().window = SDL_CreateWindow(title.c_str(), width, height, flags);
  if (Get().window == nullptr) {
    Logger::LOG("Failed to create window! SDL error: " +
                ToString(*SDL_GetError()));
  }

  SDL_ShowWindow(Get().window);

  Get().running = true;
  Get().initialized = true;
}

void Window::Close() {
  if (Engine::IsInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return;
  }
  if (IsInit() == false) {
    Logger::LOG("You must call `Window::init()` first!");
    return;
  }
  if (Get().window == nullptr) {
    return;
  }

  SDL_DestroyWindow(Get().window);

  Get().running = false;
  Get().initialized = false;
}

bool Window::Process() {
  if (Engine::IsInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return false;
  }
  if (IsInit() == false) {
    Logger::LOG("You must call `Window::init()` first!");
    return false;
  }
  if (Get().window == nullptr) {
    Logger::LOG("Window is null!");
    return false;
  }

  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    if (sdlEvent.type == SDL_EVENT_QUIT) {
      Get().running = false;
      Logger::LOG("Window should close");
    }
  }

  Vector2 dimensions = GetDimensions();

  float windowAspect = (float)dimensions.x / dimensions.y;
  float gameAspect = (float)1920 / 1080;

  Get().pillarboxed = false;

  if (windowAspect > gameAspect) {
    Get().viewportSize.x = (int32)(dimensions.y * gameAspect);
    Get().viewportSize.y = dimensions.y;

    Get().viewportPosition.x = (dimensions.x - Get().viewportSize.x) / 2;
    Get().viewportPosition.y = 0;
    Get().pillarboxed = true;
  } else {
    Get().viewportSize.x = dimensions.x;
    Get().viewportSize.y = (int32)(dimensions.x / gameAspect);

    Get().viewportPosition.x = 0;
    Get().viewportPosition.y = (dimensions.y - Get().viewportSize.y) / 2;
    Get().pillarboxed = false;
  }

  glDisable(GL_SCISSOR_TEST);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glViewport(Get().viewportPosition.x, Get().viewportPosition.y,
             Get().viewportSize.x, Get().viewportSize.y);
  glEnable(GL_SCISSOR_TEST);
  glScissor(Get().viewportPosition.x, Get().viewportPosition.y,
            Get().viewportSize.x, Get().viewportSize.y);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  return Get().running;
}

Vector2 Window::GetDimensions() {
  if (IsInit() == false) {
    Logger::LOG("You must call `Window::init()` first!");
    return Vector2();
  }
  if (Get().window == nullptr) {
    return Vector2();
  }

  int32 x;
  int32 y;
  Vector2 dimensions;

  if (SDL_GetWindowSize(Get().window, &x, &y) == false) {
    dimensions.x = 0;
    dimensions.y = 0;
    Logger::LOG("Failed to get window dimensions! SDL error: " +
                ToString(*SDL_GetError()));
  } else {
    dimensions.x = x;
    dimensions.y = y;
  }

  return dimensions;
}

void Window::SwapBuffer() {
  if (IsInit() == false) {
    Logger::LOG("You must call `Window::init()` first!");
    return;
  }
  if (Get().window == nullptr) {
    return;
  }

  SDL_GL_SwapWindow(Get().window);
}

SDL_Window *Window::GetWindow() { return Get().window; }

void Window::SetTitle(const String &title) {
  if (IsInit() == false) {
    Logger::LOG("You must call Window::init() first!");
    return;
  }
  if (Get().window == nullptr) {
    return;
  }

  SDL_SetWindowTitle(Get().window, title.c_str());
}