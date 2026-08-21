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
    Color col = Color(0.5f, 0.7f, 0.3f);
    col.r = 1.0f;

    for (int32 i = 0; i < 4; i++) {
      std::cout << "cout: " << col.data[i] << std::endl;
    }
    std::cout << "cout stop" << std::endl;

    while (Window::Process()) {
      Engine::BeginFrame();
      Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

      // Renderer::UpdateCamera(Vector3(0), Vector3(0));

      Window::SwapBuffer();

      Window::Close();
    }
  }

  Engine::Shutdown();

  return 0;
}
