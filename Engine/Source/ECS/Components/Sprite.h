#pragma once

#include <glm/glm.hpp>

struct Sprite {
	glm::vec2 texWidthHeight{256.0f, 256.0f};
	glm::vec2 texBaseCoords{ 0.0f, 256.0f };
};