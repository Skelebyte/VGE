#include "../inc/graphics.hpp"
#include <SDL3/SDL_video.h>
#include <cstdlib>

using namespace vge;

Color::Color(float rgb, float alpha) {
  r = rgb;
  g = rgb;
  b = rgb;
  a = alpha;
}

Color::Color(float red, float green, float blue, float alpha) {
  r = red;
  g = green;
  b = blue;
  a = alpha;
}

Color::~Color() {}

Color Color::White() { return Color(1.0f); }
Color Color::Black() { return Color(0.0f); }
Color Color::Red() { return Color(1.0f, 0.0f, 0.0f); }
Color Color::Green() { return Color(0.0f, 1.0f, 0.0f); }
Color Color::Blue() { return Color(0.0f, 0.0f, 1.0f); }
Color Color::Magenta() { return Color(1.0f, 0.0f, 1.0f); }
Color Color::Grey() { return Color(0.5f, 0.5f, 0.5f); }

/* ------------ Uniform ------------ */

Uniform::Uniform(const String &name, uint32 shaderID) {
  SetID(glGetUniformLocation(shaderID, name.c_str()));
  // TODO: add opengl error check

  this->name = name;
}

const String &Uniform::GetName() const { return name; }

// void Uniform::SetValue(const Matrix4x4 &value) {
//   glUniformMatrix4fv(GetID(), 1, GL_FALSE, value.data.GetData());
//   Logger::CHECK_OPENGL(
//       "Failed to set Matrix4x4 value on uniform \"" + GetName() + "\".", 2);
// }

void Uniform::SetValue(const Vector3 &value) {
  glUniform3fv(GetID(), 1, value.data);
  Logger::CHECK_OPENGL(
      "Failed to set Vector3 value on uniform \"" + GetName() + "\".", 2);
}

void Uniform::SetValue(const Vector2 &value) {
  glUniform2fv(GetID(), 1, value.data);
  Logger::CHECK_OPENGL(
      "Failed to set Vector2 value on uniform \"" + GetName() + "\".", 2);
}

void Uniform::SetValue(const Color &value) {
  glUniform3fv(GetID(), 1, value.data);
  Logger::CHECK_OPENGL(
      "Failed to set Color value on uniform \"" + GetName() + "\".", 2);
}

void Uniform::SetValue(float value) {
  glUniform1f(GetID(), value);
  Logger::CHECK_OPENGL(
      "Failed to set float value on uniform \"" + GetName() + "\".", 2);
}

void Uniform::SetValue(int32 value) {
  glUniform1i(GetID(), value);
  Logger::CHECK_OPENGL(
      "Failed to set int32 value on uniform \"" + GetName() + "\".", 2);
}

void Uniform::SetValue(bool value) {
  glUniform1i(GetID(), value);
  Logger::CHECK_OPENGL(
      "Failed to set bool value on uniform \"" + GetName() + "\".", 2);
}

/* ------------ Shader ------------ */

Shader::Shader(const String &name, const String &fragPath,
               const String &vertPath) {
  if (File::Exists(fragPath) == false) {
    Logger::LOG_FATAL("Fragment shader file \"" + fragPath +
                      "\" does not exist.");
  }
  if (File::Exists(vertPath) == false) {
    Logger::LOG_FATAL("Vertex shader file \"" + vertPath +
                      "\" does not exist.");
  }

  SetName(name);

  String fragContent = File::Read(fragPath);
  if (fragContent.empty()) {
    Logger::LOG_FATAL("Failed to read fragment shader \"" + fragPath + "\".");
  }

  String vertContent = File::Read(vertPath);
  if (vertContent.empty()) {
    Logger::LOG_FATAL("Failed to read vertex shader \"" + vertPath + "\".");
  }

  const char *cstrFrag = fragContent.c_str();
  const char *cstrVert = vertContent.c_str();

  uint32 frag = glCreateShader(GL_FRAGMENT_SHADER);
  Logger::CHECK_OPENGL("Failed to create GL_FRAGMENT_SHADER.", 1);

  glShaderSource(frag, 1, &cstrFrag, nullptr);

  glCompileShader(frag);
  Logger::CHECK_OPENGL("Failed to compile fragment shader", 1);

  IsCompileOk(frag, "Fragment");

  uint32 vert = glCreateShader(GL_VERTEX_SHADER);
  Logger::CHECK_OPENGL("Failed to create GL_VERTEX_SHADER.", 1);

  glShaderSource(vert, 1, &cstrVert, nullptr);

  glCompileShader(vert);
  Logger::CHECK_OPENGL("Failed to compile vertex shader.", 1);

  IsCompileOk(vert, "Vertex");

  SetID(glCreateProgram());

  glAttachShader(GetID(), frag);
  Logger::CHECK_OPENGL("Failed to attach fragment shader.", 1);

  glAttachShader(GetID(), vert);
  Logger::CHECK_OPENGL("Failed to attach vertex shader.", 1);

  glLinkProgram(GetID());
  Logger::CHECK_OPENGL("Failed to link shader program", 1);

  IsLinkOk();

  int32 isProgramValid = glIsProgram(GetID());
  Logger::LOG("Is shader \"" + name + "\" valid? " +
              (isProgramValid ? "YES." : "NO."));

  glDeleteShader(frag);
  glDeleteShader(vert);
}

Shader::~Shader() {
  glDeleteProgram(GetID());
  SetID(0);
}

void Shader::AddUniform(const String &name) {
  for (int32 i = 0; i < uniforms.Size(); i++) {
    if (uniforms[i].GetName() == name) {
      Logger::LOG("Uniform with the name \"" + name +
                  "\" already exists in this shader!");
      return;
    }
  }

  uniforms.Add(Uniform(name, GetID()));
}

Uniform *Shader::GetUniform(const String &name) {
  for (int32 i = 0; i < uniforms.Size(); i++) {
    if (uniforms[i].GetName() == name) {
      return &uniforms[i];
    }
  }

  Logger::LOG("Failed to find uniform \"" + name + "\" attached to shader \"" +
              GetName() + "\".");

  return nullptr;
}

void Shader::Bind() {
  glUseProgram(GetID());
  Logger::CHECK_OPENGL("glUseProgram failed!", 1);
}

void Shader::SetName(const String &name) { this->name = name; }

String &Shader::GetName() { return name; }

bool Shader::IsCompileOk(uint32 shader, const String &type) {
  int32 success;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    Pointer<char> log;
    log.Malloc(1024);
    if (!log) {
      Logger::LOG("log is not valid!");
    }

    glGetShaderInfoLog(shader, 1024, nullptr, log.GetData());
    Logger::CHECK_OPENGL(
        type + " shader compile is not ok! OpenGL log: " + log.GetData(), 0);
    return true;
  }

  return false;
}

bool Shader::IsLinkOk() {
  int32 success;

  glGetProgramiv(GetID(), GL_LINK_STATUS, &success);

  if (!success) {

    Pointer<char> log;
    log.Malloc(1024);
    glGetProgramInfoLog(GetID(), 1024, nullptr, log.GetData());

    Logger::CHECK_OPENGL(
        "Program link is not ok! OpenGL log: " + (String)log.GetData(), 0);

    return true;
  }

  return false;
}

/* ------------ VBO ------------ */

// TODO: add error checking
VBO::VBO(float *verts, size_t size) {
  glGenBuffers(1, GetID_Ptr());
  // THROW_ERROR_GL(FATAL.Derived("GL_GEN_BUFFERS_FAIL",
  //                              "Generating the VBO buffer failed!"));

  glBindBuffer(GL_ARRAY_BUFFER, GetID());
  // THROW_ERROR_GL(FATAL.Derived("GL_BIND_BUFFER_FAIL",
  //                              "Binding VBO failed (Constructor)!"));

  glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
  // THROW_ERROR_GL(FATAL.Derived("GL_BUFFER_DATA_FAIL",
  //                              "Assigning data to the VBO failed!"));
}

VBO::~VBO() { glDeleteBuffers(1, GetID_Ptr()); }

// TODO: add error checking
void VBO::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, GetID());
  // THROW_ERROR_GL(FATAL.Derived("GL_BIND_BUFFER_FAIL", "Binding VBO
  // failed!"));
}

void VBO::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

/* ------------ VAO ------------ */

// TODO: add error checking
VAO::VAO() {
  glGenVertexArrays(1, GetID_Ptr());
  // THROW_ERROR_GL(FATAL.Derived("GL_GEN_VERTEX_ARRAYS_FAIL",
  //                              "Generating the VAO buffer failed!"));
}

VAO::~VAO() { glDeleteVertexArrays(1, GetID_Ptr()); }

// TODO: add error checking
void VAO::Bind() {
  glBindVertexArray(GetID());
  // THROW_ERROR_GL(FATAL.Derived("GL_BIND_VERTEX_ARRAY_FAIL",
  //                              "Binding the VAO buffer failed!"));
}

void VAO::Unbind() { glBindVertexArray(0); }

// TODO: add error checking
void VAO::LinkAttrib(VBO &vbo, uint32 layout, uint32 components, uint32 type,
                     size_t stride, void *offset) {
  vbo.Bind();
  glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
  // THROW_ERROR_GL(FATAL.Derived("GL_VERTEX_ATTRIB_POINTER_FAIL"));

  glEnableVertexAttribArray(layout);
  // THROW_ERROR_GL(FATAL.Derived("GL_ENABLE_VERTEX_ATTRIB_ARRAY_FAIL"));

  vbo.Unbind();
}

/* ------------ EBO ------------ */

// TODO: add error checking
EBO::EBO(uint32 *indices, size_t size) {
  glGenBuffers(1, GetID_Ptr());
  // THROW_ERROR_GL(FATAL.Derived("GL_GEN_BUFFERS_FAIL",
  //                              "Generating the EBO buffer failed!"));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GetID());
  // THROW_ERROR_GL(
  //     FATAL.Derived("GL_BIND_BUFFER_FAIL", "Binding the EBO buffer
  //     failed!"));

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  // THROW_ERROR_GL(FATAL.Derived("GL_BUFFER_DATA_FAIL",
  //                              "Assigning data to the EBO buffer failed!"));
}

EBO::~EBO() { glDeleteBuffers(1, GetID_Ptr()); }

void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GetID()); }

void EBO::Unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

/* ------------ Renderer ------------ */

void Renderer::Init() {
  if (Engine::IsInit() == false) {
    Logger::LOG("You must call `Engine::init()` first!");
    return;
  }
  if (IsInit()) {
    return;
  }

  Get().gl = SDL_GL_CreateContext(Window::GetWindow());
  if (Get().gl == nullptr) {
    Logger::LOG("Failed to create OpenGL context! SDL error: " +
                ToString(*SDL_GetError()));
    return;
  }

  SDL_GL_MakeCurrent(Window::GetWindow(), Get().gl);

  if (gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress) == 0) {
    Logger::LOG("Failed to initialize glad! Remind me to come back here to add "
                "a get error function :)");
    return;
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  Get().initialized = true;
}

void Renderer::Shutdown() {
  if (IsInit() == false)
    return;

  SDL_GL_DestroyContext(Get().gl);

  Get().initialized = false;
}

void Renderer::ToggleWireframe() {
  Get().wireframe = !Get().wireframe;

  if (Get().wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}
