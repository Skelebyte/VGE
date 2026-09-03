# VGE Documentation

**Video Game Engine** _a very creative name for a very creative engine._

EXAMPLE:
  ```cpp

  #include "engine/vge.hpp"
  #include <iostream>
  
  using namespace vge;

  int main() {
    Engine::Init("VGE");
    Engine::SetTargetFps(999);

    {
      while(Window::Process()) {
        Engine::BeginFrame();

        Window::SetTitle("FPS: " + ToString(Engine::GetFps()));

        Window::SwapBuffer();
      }
    }

    Engine::Shutdown();

    return 0;
  }
  
  ```
