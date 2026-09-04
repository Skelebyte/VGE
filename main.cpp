#include "engine/inc/memory.hpp"
#include "engine/vge.hpp"
#include <iostream>

using namespace vge;

int main() {
  // Memory::Get().logFreeSizes = false;
  // Memory::Get().logMallocSizes = false;

  // Engine::Init("hi mum");
  // Engine::SetTargetFps(-1);

  Matrix a(Vector2I(3), true);
  Matrix b(Vector2I(3), true);

  for (int i = 0; i < a.GetNumberOfValues(); i++) {
    a.data[i] = i;
    b.data[i] = i;
  }

  Matrix c = a * b;

  std::cout << c.AsString() << std::endl;

  std::cout << c.GetEntry(1, 3) << std::endl;

  /*
   * why the scope brackets?
   * its so destructors get called correctly, and not after Engine::Shutdown,
   * because that would probably cause issues.
   */
  {
    // Shader defaultShader("default", "assets/shaders/default.frag",
    //                      "assets/shaders/default.vert");
    // defaultShader.AddUniform("diffuseTexture");
    // defaultShader.AddUniform("color");

    // Mesh mesh = Mesh::GeneratePlane();

    // Texture texture(4, 4, Color::White(), Color::Green());

    // // Camera camera;

    // while (Window::Process()) {
    //   Engine::BeginFrame();
    //   Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

    //   Window::SwapBuffer();
    // }
  }

  // Engine::Shutdown();

  return 0;
}
