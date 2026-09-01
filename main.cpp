#include "engine/inc/memory.hpp"
#include "engine/vge.hpp"
#include <iostream>

using namespace vge;

int main() {
  // Memory::Get().logFreeSizes = false;
  // Memory::Get().logMallocSizes = false;

  Engine::Init("hi mum");
  Engine::SetTargetFps(-1);

  /*
   * why the scope brackets?
   * its so destructors get called correctly, and not after Engine::Shutdown,
   * because that would probably cause issues.
   */

  Pointer<float> gurt;

  {
    Shader defaultShader = Shader("default", "assets/shaders/default.frag",
                                  "assets/shaders/default.vert");
    defaultShader.AddUniform("diffuseTexture");
    defaultShader.AddUniform("color");

    Mesh mesh = Mesh::GeneratePlane();

    Texture texture = Texture(4, 4, Color::White(), Color::Green());

    Camera camera = Camera();

    while (Window::Process()) {
      Engine::BeginFrame();
      Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

      Window::SwapBuffer();
    }
  }

  Engine::Shutdown();

  return 0;
}
