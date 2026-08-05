#include "engine/asset.hpp"
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
  Engine::fullInit("hi mum");

  // Texture tex = Asset::load(
  //     "assets/textures/image.png");
  // TODO: return to asset loading... i want to have some system to do it but
  // idk what or how exactly

  while (Window::process()) {
    Engine::beginFrame();

    Window::swapBuffer();
  }

  Engine::fullShutdown();

  return 0;
}