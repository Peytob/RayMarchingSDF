#version 330 core

layout (location = 0) in vec3 l_position;

void main() {
    gl_Position.xyz = l_position;
    gl_Position.w = 1.0;
}
