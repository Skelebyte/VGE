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

  Matrix<1, 2> a;
  a[0] = 1;
  a[1] = 2;

  Matrix<2, 1> b;
  a[0] = 1;
  a[1] = 2;

  Matrix<2, 2> c = Matrix<2, 2>::Multiply(a, b);

  {
    Shader defaultShader("default", "assets/shaders/default.frag",
                         "assets/shaders/default.vert");
    defaultShader.AddUniform("diffuseTexture");
    defaultShader.AddUniform("color");

    Mesh mesh = Mesh::GeneratePlane();

    Texture texture(4, 4, Color::White(), Color::Green());

    Camera camera;

    while (Window::Process()) {
      Engine::BeginFrame();
      Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

      camera.Process();

      Window::SwapBuffer();
    }
  }

  Engine::Shutdown();

  return 0;
}
