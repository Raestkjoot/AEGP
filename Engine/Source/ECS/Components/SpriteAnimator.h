#pragma once

#include "ECS/Systems/SpriteRenderer.h"
#include "ServiceLocator.h"

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>
#include <vector>
#include <map>
#include <string>

struct SpriteAnimator {
	bool isPlaying = true;
	bool isLooping = true;
	float speed = 1.0f;
	float frameTimer = 0.0f;
	std::map<std::string, std::vector<SpriteRenderer::SpriteAtlasData>> animations;
	std::vector<SpriteRenderer::SpriteAtlasData>* curAnimation;
	int curFrame;
};