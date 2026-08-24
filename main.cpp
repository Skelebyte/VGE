#include "engine/inc/asset.hpp"
#include "engine/inc/common.hpp"
#include "engine/inc/graphics.hpp"
#include "engine/inc/memory.hpp"
#include "engine/inc/vector2.hpp"
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
    Shader defaultShader = Shader("default", "assets/shaders/default.frag",
                                  "assets/shaders/default.vert");
    defaultShader.AddUniform("diffuseTexture");
    defaultShader.AddUniform("color");

    Mesh mesh = Mesh::GeneratePlane();

    Texture texture = Texture(4, 4, Color::White(), Color::Green());

    while (Window::Process()) {
      Engine::BeginFrame();
      Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

      Renderer::UpdateCamera(Vector3(0), Vector3(0));

      Window::SwapBuffer();
    }
  }

  Engine::Shutdown();

  return 0;
}
