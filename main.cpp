#include "engine/inc/memory.hpp"
#include "engine/vge.hpp"
#include <iostream>

using namespace vge;

int main() {
  Memory::Get().logFreeSizes = false;
  Memory::Get().logMallocSizes = false;

  // Engine::Init("hi mum");

  // Matrix a(3, true);
  // for (int i = 0; i < a.TotalEntries(); i++) {
  //   a.data[i] = i;
  // }

  // Matrix b(3, true);
  // for (int i = 0; i < b.TotalEntries(); i++) {
  //   b.data[i] = i;
  // }

  // Matrix c = a * b;

  // for (int i = 0; i < c.TotalEntries(); i++) {
  //   std::cout << c.data[i] << " ";
  // }
  // std::cout << std::endl;
  // std::cout << c.AsString() << std::endl;

  // Matrix d(4, true);
  // d.SetEntry(1, 2, 999);
  // std::cout << d.AsString() << std::endl;

  // Matrix tm(4, true);
  // tm.Transform(Vector3(3, -5, 7), Vector3(45, -65, 12), Vector3(1));
  // std::cout << tm.AsString() << std::endl;

  // Matrix rm(3, true);
  // rm.SetRotation(Vector3(45, -65, 12));
  // std::cout << rm.AsString() << std::endl;

  // Matrix sm(4, true);
  // sm.SetScale(Vector3(2));
  // std::cout << sm.AsString() << std::endl;

  // Transform3D transform(Vector3(3, -5, 7), Vector3(45, -65, 12), Vector3(1));
  // std::cout << transform.Forward().Length() << std::endl;

  Matrix m(4, true);
  m.LookAt(Vector3(5, 0, 0), Vector3(0, 1, 0), Vector3(0, 12, -6));

  std::cout << m.AsString() << std::endl;

  // std::cout << Vector3(3, 4, 0).Normalized().Length() << std::endl;

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
