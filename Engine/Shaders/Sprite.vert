#version 330 core

layout (location = 0) in vec2 Pos;
layout (location = 1) in uint QuadID;

void main() {
   gl_Position = vec4(Pos, 0.5, 1.0);
}