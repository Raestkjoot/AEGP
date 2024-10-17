#pragma once

#include "ECS/System.h"

#include <glm/glm.hpp>

class ClearRenderer : public System {
public:
	void Start() override;
	void Update() override;
	void End() override;

private:
	void Init(entt::registry* registry) override;

	glm::vec4 _clearColor{ 0.2f, 0.3f, 0.3f, 1.0f };
};