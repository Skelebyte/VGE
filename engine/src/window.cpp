#include "../inc/window.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>

using namespace vge;

void Window::init(String title, uint32 width, uint32 height, bool allowResize,
                  bool fullscreen) {
  if (Engine::isInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return;
  }
  if (isInit() || get().window != nullptr) {
    return;
  }

  uint32 flags = SDL_WINDOW_OPENGL;
  if (allowResize) {
    flags |= SDL_WINDOW_RESIZABLE;
  }
  if (fullscreen) {
    flags |= SDL_WINDOW_FULLSCREEN;
  }

  get().window = SDL_CreateWindow(title.c_str(), width, height, flags);
  if (get().window == nullptr) {
    Logger::LOG("Failed to create window! SDL error: " +
                toString(*SDL_GetError()));
  }

  SDL_ShowWindow(get().window);

  get().running = true;
  get().initialized = true;
}

void Window::close() {
  if (Engine::isInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return;
  }
  if (isInit() == false) {
    Logger::LOG("You must call `Window::init()` first!");
    return;
  }
  if (get().window == nullptr) {
    return;
  }

  SDL_DestroyWindow(get().window);

  get().running = false;
  get().initialized = false;
}

bool Window::process() {
  if (Engine::isInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return false;
  }
  if (isInit() == false) {
    Logger::LOG("You must call `Window::init()` first!");
    return false;
  }
  if (get().window == nullptr) {
    Logger::LOG("Window is null!");
    return false;
  }

  SDL_Event sdlEvent;
  while (SDL_PollEvent(&sdlEvent)) {
    if (sdlEvent.type == SDL_EVENT_QUIT) {
      get().running = false;
      Logger::LOG("Window should close");
    }
  }

  Vector2 dimensions = getDimensions();

  float windowAspect = (float)dimensions.x / dimensions.y;
  float gameAspect = (float)1920 / 1080;

  get().pillarboxed = false;

  if (windowAspect > gameAspect) {
    get().viewportSize.x = (int32)(dimensions.y * gameAspect);
    get().viewportSize.y = dimensions.y;

    get().viewportPosition.x = (dimensions.x - get().viewportSize.x) / 2;
    get().viewportPosition.y = 0;
    get().pillarboxed = true;
  } else {
    get().viewportSize.x = dimensions.x;
    get().viewportSize.y = (int32)(dimensions.x / gameAspect);

    get().viewportPosition.x = 0;
    get().viewportPosition.y = (dimensions.y - get().viewportSize.y) / 2;
    get().pillarboxed = false;
  }

  glDisable(GL_SCISSOR_TEST);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glViewport(get().viewportPosition.x, get().viewportPosition.y,
             get().viewportSize.x, get().viewportSize.y);
  glEnable(GL_SCISSOR_TEST);
  glScissor(get().viewportPosition.x, get().viewportPosition.y,
            get().viewportSize.x, get().viewportSize.y);

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  return get().running;
}

Vector2 Window::getDimensions() {
  if (isInit() == false) {
    Logger::LOG("You must call `Window::init()` first!");
    return Vector2();
  }
  if (get().window == nullptr) {
    return Vector2();
  }

  int32 x;
  int32 y;
  Vector2 dimensions;

  if (SDL_GetWindowSize(get().window, &x, &y) == false) {
    dimensions.x = 0;
    dimensions.y = 0;
    Logger::LOG("Failed to get window dimensions! SDL error: " +
                toString(*SDL_GetError()));
  } else {
    dimensions.x = x;
    dimensions.y = y;
  }

  return dimensions;
}

void Window::swapBuffer() {
  if (isInit() == false) {
    Logger::LOG("You must call `Window::init()` first!");
    return;
  }
  if (get().window == nullptr) {
    return;
  }

  SDL_GL_SwapWindow(get().window);
}

SDL_Window *Window::getWindow() { return get().window; }