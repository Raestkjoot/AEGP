#pragma once

#include "ECS/System.h"

#include "glm/glm.hpp"

class MoveSystem : public System {
public:
	void Start() override;
	void Update(float delta) override;

private:
	void HandleInput(bool isGrounded);

	glm::vec2 _velocity;
	float _moveDirection;
	bool _jump;
	bool _jumpReleased = true;

	float _maxVelocity = 2.0f;
	float _groundMoveAcceleration = 28.0f;
	float _groundStopAcceleration = 20.0f;
	float _airMoveAcceleration = 16.0f;
	float _jumpPower = 6.0f;
	float _jumpHeldGravity = 10.0f;
	float _jumpReleasedGravity = 25.0f;
};