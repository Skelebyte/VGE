#include "engine/inc/asset.hpp"
#include "engine/inc/common.hpp"
#include "engine/inc/graphics.hpp"
#include "engine/inc/memory.hpp"
#include "engine/inc/vector2.hpp"
#include "engine/inc/vector2i.hpp"
#include "engine/vge.hpp"
#include <iostream>

using namespace vge;

int main() {
  // Memory::Get().logFreeSizes = false;
  // Memory::Get().logMallocSizes = false;

  Engine::Init("hi mum");
  Engine::SetTargetFps(-1);

  int d = 3;
  Matrix m4 = Matrix(Vector2I(d), true);

  for (int i = 0; i < m4.GetNumberOfValues(); i++) {
    std::cout << m4.data[i] << ", ";
    if ((i + 1) % d == 0) {
      std::cout << std::endl;
    }
  }

  /*
   * why the scope brackets?
   * its so destructors get called correctly, and not after Engine::Shutdown,
   * because that would probably cause issues.
   */

  {
    // Shader defaultShader = Shader("default", "assets/shaders/default.frag",
    //                               "assets/shaders/default.vert");
    // defaultShader.AddUniform("diffuseTexture");
    // defaultShader.AddUniform("color");

    // Mesh mesh = Mesh::GeneratePlane();

    // Texture texture = Texture(4, 4, Color::White(), Color::Green());

    // Camera camera = Camera();

    while (Window::Process()) {
      Engine::BeginFrame();
      Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

      Window::SwapBuffer();
    }
  }

  Engine::Shutdown();

  return 0;
}
