#version 460 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;

out vec4 vertexColor;

uniform mat4 P;
uniform mat4 R;

void main() {
  gl_Position = P * R * vec4(aPosition, 1.0);
  vertexColor = aColor;
}