#include "engine/inc/common.hpp"
#include "engine/inc/graphics.hpp"
#include "engine/inc/list.hpp"
#include "engine/inc/logger.hpp"
#include "engine/vge.hpp"
#include <iostream>

using namespace vge;

int main() {
  Engine::Init("hi mum");
  Engine::SetTargetFps(-1);

  /*
   * why the scope brackets?
   * its for destructors of Texture and any future
   * structs
   */

  {
    while (Window::Process()) {
      Engine::BeginFrame();

      Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

      // Renderer::UpdateCamera(Vector3(0), Vector3(0));

      Window::SwapBuffer();
    }
  }

  Engine::Shutdown();

  return 0;
}
