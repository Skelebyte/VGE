#version 330 core

out vec4 FragColor;

in vec3 pos;
in vec2 textureCoord;
in vec3 normal;

uniform sampler2D diffuseTexture;
uniform vec4 color = vec3(1.0, 1.0, 1.0, 1.0);

void main() {
  vec4 output = vec4(0);

  output = texture(diffuseTexture, textureCoord) * color;

  FragColor = output;
}