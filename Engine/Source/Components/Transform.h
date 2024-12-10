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
		if (args.contains("Position")) {
			position = glm::vec2(args.at("Position").at(0), args.at("Position").at(1));
		}
		if (args.contains("Rotation")) {
			rotation = args.at("Rotation").get<float>();
		}
		if (args.contains("Scale")) {
			scale = glm::vec2(args.at("Scale").at(0), args.at("Scale").at(1));
		}
	}
};