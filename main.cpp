#include "engine/inc/memory.hpp"
#include "engine/vge.hpp"
#include <iostream>

using namespace vge;

int main() {
  // Memory::Get().logFreeSizes = false;
  // Memory::Get().logMallocSizes = false;

  // Engine::Init("hi mum");

  /*
   * why the scope brackets?
   * its so destructors get called correctly, and not after Engine::Shutdown,
   * because that would probably cause issues.
   */

  Matrix<1, 2> a;
  for (int i = 0; i < a.ENTRIES; i++) {
    a[i] = i + 1;
  }
  Matrix<1, 2> b;
  for (int i = 0; i < b.ENTRIES; i++) {
    b[i] = i + 1;
  }
  std::cout << "a: \n" << b.AsString() << std::endl;
  std::cout << "b: \n" << b.AsString() << std::endl;
  Matrix c = a * b;
  std::cout << "a * b = " << std::endl;
  std::cout << c.AsString() << std::endl;

  for (int i = 0; i < c.ENTRIES; i++) {
    std::cout << c[i] << ", ";
  }
  std::cout << std::endl;

  // Matrix<2, 1> b;
  // b.data[0] = 1;
  // b.data[1] = 2;

  // Matrix c = a * b;

  // std::cout << c.AsString();

  // {
  //   Shader defaultShader("default", "assets/shaders/default.frag",
  //                        "assets/shaders/default.vert");
  //   defaultShader.AddUniform("diffuseTexture");
  //   defaultShader.AddUniform("color");

  //   Mesh mesh = Mesh::GeneratePlane();

  //   Texture texture(4, 4, Color::White(), Color::Green());

  //   Camera camera;

  //   while (Window::Process()) {
  //     Engine::BeginFrame();
  //     Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

  //     camera.Process();

  //     Window::SwapBuffer();
  //   }
  // }

  // Engine::Shutdown();

  return 0;
}
