#version 330 core

layout(location = 0) in vec3 i_pos;
layout(location = 1) in vec2 i_texture_coord;
layout(location = 2) in vec3 i_normal;

out vec3 pos;
out vec2 texture_coord;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  pos = vec3(model * vec4(i_pos, 1.0));
  gl_Position = projection * view * model * vec4(i_pos, 1.0);

  // gl_Position = vec4(i_pos * 0.1, 1.0);

  texture_coord = i_texture_coord;
  normal = mat3(transpose(inverse(model))) * i_normal;
  // normal = i_normal;
}