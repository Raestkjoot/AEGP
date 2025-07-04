#pragma once

#include "System.h"

#include <glm/glm.hpp>

class ClearRenderer : public System {
public:
	void Start() override;
	void Update(float delta) override;

private:
	void ClearFrame();

	glm::vec4 _clearColor{ 0.196f, 0.2f, 0.18f, 1.0f };
};