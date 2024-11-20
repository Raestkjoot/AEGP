#pragma once

#include <random>

namespace Random {
	static std::random_device rd;
	static std::mt19937 gen(rd());

	int Range(int min, int max) {
		std::uniform_int_distribution<int> dist(min, max);
		return dist(gen);
	}

	float Range(float min, float max) {
		std::uniform_real_distribution<float> dist(min, max);
		return dist(gen);
	}
}