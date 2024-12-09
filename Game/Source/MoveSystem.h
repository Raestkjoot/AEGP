#pragma once

#include "Systems/System.h"
#include "Audio/AudioArray.h"

#include "glm/glm.hpp"

class MoveSystem : public System {
public:
	void Start() override;
	void Update(float delta) override;

private:
	void HandleInput();
	bool ShouldJump();

	glm::vec2 _velocity;
	float _moveDirection;
	bool _isGrounded = false;
	bool _readyToJumpAgain = true;
	bool _jumpReleased = true;
	float _jumpPressedTime = -100.0f;
	float _passedTime = 0.0f;
	float _lastGroundedTime = 0.0f;
	bool _wasGroundedLastFrame;
	float _initialAirHorizontalVelocity;

#pragma region tweak values
	float _maxHorizontalSpeed = 3.2f;
	float _groundAcceleration = 20.0f;
	float _groundDeceleration = 25.0f;
	float _airHorizontalAcceleration = 17.0f;
	// Air vert acc is applied when the player moves against the initial horizontal input,
	// giving a feel of converting hori velocity to vert velocity.
	float _airVerticalAcceleration = 1.8f;
	float _jumpPower = 6.5f;
	// gravity after a jump depends on whether jump is being held down or not.
	float _gravity = 25.0f;
	float _jumpHeldGravity = 10.0f;
	// Store jump input for this long, after player releases jump button
	float _jumpCache1 = 0.08f;
	// Store jump input for this long, while player is holding jump button
	float _jumpCache2 = 0.4f;
	// Let player still jump for this time, after running off an edge
	float _coyoteTime = 0.1f;
#pragma endregion tweak values

	AudioArray _jumpSounds;
};