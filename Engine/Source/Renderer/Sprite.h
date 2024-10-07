#pragma once

//#include "Renderer.h"
#include "glm/glm.hpp"


struct SpriteData {
	glm::vec2 texWidthHeight;
	glm::vec2 texBaseCoords;
	glm::mat3x4 transform; // mat3x3, padded for std140

	SpriteData(const glm::vec2& texWidthHeight, const glm::vec2& texBaseCoords, const glm::mat3x3& transform) :
		texWidthHeight(texWidthHeight),
		texBaseCoords(texBaseCoords),
		transform(transform) { }
};

class Sprite {
public:


private:
	unsigned int _id;
};
