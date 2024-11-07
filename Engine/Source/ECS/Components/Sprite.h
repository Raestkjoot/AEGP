#pragma once

#include "ECS/Systems/SpriteRenderer.h"
#include "ServiceLocator.h"

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

struct Sprite {
	glm::vec2 texWidthHeight{256.0f, 256.0f};
	glm::vec2 texBaseCoords{ 0.0f, 256.0f };
	glm::bvec2 flip{ false, false };

	Sprite() = default;
	Sprite(glm::vec2 texWidthHeight, glm::vec2 texBaseCoords) :
		texWidthHeight(texWidthHeight),
		texBaseCoords(texBaseCoords) {
	}
	Sprite(SpriteRenderer::SpriteAtlasData spriteData) :
		texWidthHeight(spriteData.texWidthHeight),
		texBaseCoords(spriteData.texBaseCoords) {
	}
	Sprite(nlohmann::json args) {
		SpriteRenderer::SpriteAtlasData spriteData =
			ServiceLocator::GetSpriteRenderer()->GetSprite(args.at("Name"));

		texWidthHeight = spriteData.texWidthHeight;
		texBaseCoords = spriteData.texBaseCoords;
	}
};