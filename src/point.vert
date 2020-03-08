#version 150 core
uniform float aspect;
in vec4 position;
void main() {
  gl_Position = vec4(position.x / aspect, position.yzw);
}