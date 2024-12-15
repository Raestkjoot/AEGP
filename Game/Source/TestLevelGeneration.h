#pragma once

#include <glm/glm.hpp>

class TestLevelGeneration {
public:
	void GenerateLevel();

	unsigned int _numOfBoxesToSpawn = 900;
	float _boxesPerRow = 10.f;
	float _scale = 0.5f;
	glm::vec2 _distance{ 1.1f, 1.4f };
};