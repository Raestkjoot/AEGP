#include "SpriteRenderPass.h"

#include "Renderer.h"
#include "Logger.h"

#include <vector>

#define NUM_OF_VERTS 6

SpriteRenderPass::SpriteRenderPass(unsigned int maxNumSprites) 
	: _maxNumSprites(maxNumSprites) { }

void SpriteRenderPass::Init() {
	_shader.Load("Engine/Shaders/Sprite.vert", "Engine/Shaders/Sprite.frag");

	#pragma region VertexArray
	// Generate vertices for the max number of quads
	glm::vec2 quadVertexPositions[] = {
		glm::vec2(0.0f, 0.0f), // bottom left
		glm::vec2(0.0f, 1.0f), // top left
		glm::vec2(1.0f, 1.0f), // top right
		glm::vec2(0.0f, 0.0f), // bottom left
		glm::vec2(1.0f, 1.0f), // top right
		glm::vec2(1.0f, 0.0f)  // bottom right
	};

	std::vector<Vertex> vertices;
	vertices.reserve(_maxNumSprites * NUM_OF_VERTS);

	for (unsigned int quadIter = 0; quadIter < _maxNumSprites; ++quadIter) {
		for (unsigned int vertIter = 0; vertIter < NUM_OF_VERTS; ++vertIter) {
			vertices.emplace_back(
				quadVertexPositions[vertIter],
				quadIter
			);
		}
	}


	// Bind buffers
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Add data
	unsigned int size = vertices.size() * sizeof(Vertex);
	glBufferData(GL_ARRAY_BUFFER, size, &vertices[0], GL_STATIC_DRAW);
	// Position attribute (location = 0)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// QuadID attribute (location = 1)
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*)offsetof(Vertex, quadID));
	glEnableVertexAttribArray(1);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	#pragma endregion VertexArray

	#pragma region QuadInfoBuffer
	
	// TODO

	#pragma endregion QuadIDBuffer
}

void SpriteRenderPass::Render() {
	_shader.Use();
	glBindVertexArray(_vao);

	// Drawcall
	glDrawArrays(GL_TRIANGLES, 0, _curNumSprites * NUM_OF_VERTS);
}

unsigned int SpriteRenderPass::AddSprite() {
	return _curNumSprites += 10;
}