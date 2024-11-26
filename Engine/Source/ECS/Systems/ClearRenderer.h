#pragma once

#include "ECS/System.h"

#include <glm/glm.hpp>

class ClearRenderer : public System {
public:
	void Start() override;
	void Update(float delta) override;

private:
	void ClearFrame();

	glm::vec4 _clearColor{ 0.31f, 0.3f, 0.305f, 1.0f };
};