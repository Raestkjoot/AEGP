#version 330 core

layout (location = 0) in vec2 Pos;
layout (location = 1) in uint QuadID;

// Padding might be bad here https://registry.khronos.org/OpenGL/extensions/ARB/ARB_uniform_buffer_object.txt
struct Quad {
	vec2 TexBaseCoords;
	vec2 TexWidthHeight;
	mat3x3 Transform;
	//vec2 Offset
};

#define MAX_QUADS 1000
layout (std140) uniform QuadInfo {
	Quad quad[MAX_QUADS];
};

uniform mat3x3 CameraMatrix;
//uniform ivec2 WindowSize;
//#define WindowSize vec2(512, 512)

out vec2 TexCoords;

void main() {
	// TODO: Divide by screen size
   TexCoords = (quad[QuadID].TexBaseCoords + Pos * quad[QuadID].TexWidthHeight) / 512;
   vec3 position = CameraMatrix * quad[QuadID].Transform * vec3(Pos.xy, 1.0f);
   gl_Position = vec4(position.xy, 0.5f, position.z);
}