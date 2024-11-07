#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

struct Transform {
	glm::vec2 position{ 0.0f, 0.0f };
	float rotation{ 0.0f };
	glm::vec2 scale{ 1.0f, 1.0f };

	Transform() = default;
	Transform(glm::vec2 position) :
		position(position),
		rotation(0.0f),
		scale({ 1.0f, 1.0f }) {
	}
	Transform(nlohmann::json args) {
		position = glm::vec2(args.at("Position").at(0), args.at("Position").at(1));
	}
};