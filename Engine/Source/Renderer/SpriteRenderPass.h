#pragma once

#include "RenderPass.h"

#include <glm/glm.hpp>

class SpriteRenderPass : public RenderPass {
public:
	SpriteRenderPass(unsigned int maxNumSprites = 1000);

	void Init() override;
	void Render() override;

	unsigned int AddSprite();

private:
	struct Vertex
	{
		glm::vec2 position;
		unsigned int quadID;

		Vertex(const glm::vec2& position, unsigned int quadID) : 
			position(position), 
			quadID(quadID) { }
	};

	unsigned int _maxNumSprites;
	unsigned int _curNumSprites = 0;

	unsigned int _vao = 0;
	unsigned int _shaderProgram = 0;
	unsigned int _quadInfoBuffer = 0;
};