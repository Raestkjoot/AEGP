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
uniform vec2 Offset = vec2(-0.5f, -0.5f);
uniform float TexSize = 512.0f;

out vec2 TexCoords;

void main() {
	// TODO: Divide by total texture size
   TexCoords = (quad[QuadID].TexBaseCoords + Pos * quad[QuadID].TexWidthHeight) / TexSize;
   vec2 offsetPosition = Pos + Offset;
   vec3 position = CameraMatrix * quad[QuadID].Transform * vec3(offsetPosition, 1.0f);
   gl_Position = vec4(position.xy, 0.5f, 1.0f);
}