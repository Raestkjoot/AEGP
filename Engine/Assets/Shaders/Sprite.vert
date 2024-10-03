#version 330 core

layout (location = 0) in vec2 Pos;
layout (location = 1) in uint QuadID;

#define MAX_QUADS 100
layout (std140) uniform QuadInfo {
	//vec2 TexBaseCoords[MAX_QUADS];
	vec2 TexWidthHeight[MAX_QUADS];
	//vec2 Offset[MAX_QUADS];
	//mat3x3 Transform[MAX_QUADS]; // Padding might be bad here https://registry.khronos.org/OpenGL/extensions/ARB/ARB_uniform_buffer_object.txt
};

//uniform ivec2 WindowSize;
//#define WindowSize vec2(512, 512)

out vec2 TexCoords;

void main() {
   TexCoords = (Pos * TexWidthHeight[QuadID] + vec2(0, 256)) / 512; // TexBaseCoords[QuadID] + 
   gl_Position = vec4(Pos, 0.5f, 1.0f);
//   vec2 basePos = Pos + Offset[QuadID] * TexWidthHeight[QuadID];
//   // TODO: Transformed position
//   vec2 ndcPos = 2 * basePos / WindowSize - 1;
//   gl_Position = vec4(ndcPos, 0.5, 1.0);
}