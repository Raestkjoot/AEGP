#pragma once

#include <glm/glm.hpp>

struct Camera2D {
	glm::vec2 position{};
	float rotation = 0.0f;
	float zoom = 0.3f;

	glm::vec2 widthHeight{1080.f, 1080.f};

	Camera2D() = default;
	Camera2D(glm::vec2 widthHeight) : widthHeight(widthHeight) {}
};