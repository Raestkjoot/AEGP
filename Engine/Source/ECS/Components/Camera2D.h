#pragma once

#include <glm/glm.hpp>

struct Camera2D {
	glm::vec2 position{};
	float rotation = 0.0f;
	float zoom = 1.0f;

	glm::vec2 widthHeight{512.f, 512.f};

	Camera2D() = default;
	Camera2D(glm::vec2 widthHeight) : widthHeight(widthHeight) {}
};