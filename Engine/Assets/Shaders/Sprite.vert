#version 330 core

layout (location = 0) in vec2 Pos;
layout (location = 1) in uint QuadID;

#define MAX_QUADS 100
uniform QuadInfo {
	mat3x3 Transform[MAX_QUADS];
	vec2 TexCoords[MAX_QUADS];
	vec2 TexWidthHeight[MAX_QUADS];
	// TODO: Might add a vec2 anchor - or a 6 option anchor using a byte maybe.
};

out vec2 TexCoord;

void main() {
	vec2 ScaledPosition = Pos * TexWidthHeight[QuadID];
   gl_Position = vec4(ScaledPosition, 0.5, 1.0);
   TexCoord = TexCoords[QuadID] + ScaledPosition;
}