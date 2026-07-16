#version 330 core

out vec4 FragColor;

in vec3 pos;
in vec2 texture_coord;
in vec3 normal;

uniform sampler2D diffuse_texture;
uniform vec3 color = vec3(1.0, 1.0, 1.0);

void main() {
  vec4 output = vec4(0);

  output = texture(diffuse_texture, texture_coord) * vec4(color, 1.0);

  FragColor = output;
}