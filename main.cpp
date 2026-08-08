#include "engine/vge.hpp"
#include <iostream>

using namespace vge;

int main() {
  Engine::init("hi mum");

  {
    Texture tex = Texture("assets/textures/image.png");

    while (Window::process()) {
      Engine::beginFrame();

      Window::swapBuffer();
    }
  }

  Engine::shutdown();

  return 0;
}