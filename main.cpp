#include "engine/common.hpp"
#include "engine/engine.hpp"
#include "engine/graphics.hpp"
#include "engine/logger.hpp"
#include "engine/matrix4.hpp"
#include "engine/time.hpp"
#include "engine/vector3.hpp"
#include "engine/window.hpp"
#include <iostream>

using namespace vge;

int main() {
  Engine::init();
  Window::init("hi mum", 600, 400);
  Renderer::init();

  while (Window::process()) {
    Engine::beginFrame();

    Window::swapBuffer();
  }

  Renderer::shutdown();
  Window::close();
  Engine::shutdown();

  return 0;
}