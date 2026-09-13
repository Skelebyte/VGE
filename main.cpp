#include "engine/inc/memory.hpp"
#include "engine/vge.hpp"
#include <iostream>

using namespace vge;

int main() {
  Memory::Get().logFreeSizes = false;
  Memory::Get().logMallocSizes = false;

  Engine::Init("hi mum");

  /*
   * why the scope brackets?
   * its so destructors get called correctly, and not after Engine::Shutdown,
   * because that would probably cause issues.
   */

  Matrix<2, 2> a;
  for (int i = 0; i < a.ENTRIES; i++) {
    a[i] = i;
  }
  std::cout << "Before:\n" << a.AsString() << std::endl;
  Matrix<2, 2> b;
  for (int i = 0; i < b.ENTRIES; i++) {
    b[i] = -i;
  }
  a = b;
  std::cout << "After:\n" << a.AsString() << std::endl;

  Matrix<4, 4> c;
  c.Transform(Vector3(1, 10, -5.5), Vector3(43, 94, -12),
              Vector3(0.75f, 0.75f, 0.75f));
  std::cout << "C:\n" << c.AsString();

  {
    Shader defaultShader("default", "assets/shaders/default.frag",
                         "assets/shaders/default.vert");
    defaultShader.AddUniform("diffuseTexture");
    defaultShader.AddUniform("color");

    Mesh mesh = Mesh::GeneratePlane();

    Texture texture(4, 4, Color::White(), Color::Green());

    // Camera camera;

    while (Window::Process()) {
      Engine::BeginFrame();
      Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

      // camera.Process();

      Window::SwapBuffer();
    }
  }

  Engine::Shutdown();

  return 0;
}
