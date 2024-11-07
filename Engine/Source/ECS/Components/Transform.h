#pragma once

#include <glm/glm.hpp>

struct Transform {
	glm::vec2 position;
	float rotation;
	glm::vec2 scale{ 1.0f, 1.0f };

	Transform() = default;
	Transform(glm::vec2 position) :
		position(position),
		rotation(0.0f),
		scale({ 1.0f, 1.0f }) {

	}
};