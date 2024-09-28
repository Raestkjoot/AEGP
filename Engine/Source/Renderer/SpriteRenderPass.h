#pragma once

#include "RenderPass.h"

#include <glm/glm.hpp>

#include <vector>

class SpriteRenderPass : public RenderPass {
public:
	SpriteRenderPass();

	void Init() override;
	void Render() override;

	int16_t AddSprite();

private:
	std::vector<glm::vec3> _vertices;
	std::vector<int> _indices;
	int _curTopIndex = -1;
	unsigned int _shaderProgram;
	unsigned int _vbo, _vao, _ebo;
};