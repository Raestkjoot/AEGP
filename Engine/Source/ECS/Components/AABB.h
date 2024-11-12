#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

struct AABB {
	glm::vec2 extents;

	AABB(glm::vec2 extents) : extents(extents) {}
	AABB(float xExtent, float yExtent) : extents({xExtent, yExtent}) {}
	AABB(nlohmann::json args) {
		extents = glm::vec2(args.at("Size").at(0), args.at("Size").at(1));
	}
};