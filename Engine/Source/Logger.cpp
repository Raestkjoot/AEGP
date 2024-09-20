#include "Logger.h"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

namespace Logger {
	glm::vec2 glmVec{ 0.1f, 2.0f };

	void Print(const std::string& str) {
		spdlog::info("X = {}", glmVec.x);
	}
}