#pragma once

#include <glm/glm.hpp>

#include "Audio/FixedSizeAudioArray.h"

struct PlayerController {
	bool isGrounded;
	bool isTouchingRight;
	bool isTouchingLeft;
	bool isTouchingTop;
	glm::vec2 offset;

	glm::vec2 velocity;
	float moveDirection;
	bool readyToJumpAgain = true;
	bool jumpReleased = true;
	float jumpPressedTime = -100.0f;
	float passedTime = 0.0f;
	float lastGroundedTime = 0.0f;
	bool wasGroundedLastFrame;
	float initialAirHorizontalVelocity;

	#pragma region tweak values
	float maxHorizontalSpeed = 3.2f;
	float groundAcceleration = 20.0f;
	float groundDeceleration = 25.0f;
	float airHorizontalAcceleration = 17.0f;
	// Air vert acc is applied when the player moves against the initial horizontal input,
	// giving a feel of converting hori velocity to vert velocity.
	float airVerticalAcceleration = 1.8f;
	float jumpPower = 6.5f;
	// gravity after a jump depends on whether jump is being held down or not.
	float gravity = 25.0f;
	float jumpHeldGravity = 10.0f;
	// Store jump input for this long, after player releases jump button
	float jumpCache1 = 0.08f;
	// Store jump input for this long, while player is holding jump button
	float jumpCache2 = 0.4f;
	// Let player still jump for this time, after running off an edge
	float coyoteTime = 0.1f;
	#pragma endregion tweak values
};