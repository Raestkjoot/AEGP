#pragma once

#include "ECS/System.h"

#include "glm/glm.hpp"

class MoveSystem : public System {
public:
	void Start() override;
	void Update(float delta) override;

private:
	glm::vec2 _moveDirection;
	float _rotationDirection;
	glm::vec2 _scaleDirection;
	float _zoomDirection;

	float _moveSpeed = 1.5f;
	float _rotationSpeed = 4.0f;
	float _scaleSpeed = 0.8f;
	float _zoomSpeed = 0.4f;
};