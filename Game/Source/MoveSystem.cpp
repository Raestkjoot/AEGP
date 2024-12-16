#include "MoveSystem.h"

#include "PlayerController.h"
#include "Application.h"
#include "Input/InputManager.h"
#include "Audio/Audio.h"
#include "Audio/AudioArray.h"
#include "Components/Transform.h"
#include "Components/Sprite.h"
#include "Components/SpriteAnimator.h"
#include "Components/Camera2D.h"
#include "Components/Collider_Dynamic.h"
#include "Utils/Logger.h"
#include "Utils/ServiceLocator.h"

#include <glfw/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

void MoveSystem::Start() {
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_LEFT);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_A);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_RIGHT);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_D);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_UP);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_W);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_SPACE);

	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_ESCAPE);

	auto playerView = _registry->view<Transform, Sprite, PlayerController>();
	auto player = playerView.front();

	auto& animator = _registry->emplace<SpriteAnimator>(player);
	animator.animations["Idle"] = ServiceLocator::GetSpriteRenderer()->GetSpriteAnim("Idle");
	animator.animations["Run"] = ServiceLocator::GetSpriteRenderer()->GetSpriteAnim("Run");
	animator.animations["Jump"] = ServiceLocator::GetSpriteRenderer()->GetSpriteAnim("Jump");
	animator.curAnimation = &animator.animations.at("Idle");
	animator.speed = 16.f;

	auto& pContrl = _registry->get<PlayerController>(player);
	pContrl.offset = glm::vec2(0.0f, -0.032f);

	_jumpSound.AddAudioFile("Assets/sfx_jump_purr.wav");
	_jumpSound.AddAudioFile("Assets/sfx_land_purr.wav");
	_jumpSound.SetVolume(2.5f);
	_jumpSound.SetPitchRange({ 0.9f, 1.1f });
	_footstepSounds.AddAudioFile("Assets/sfx_footstep01.wav");
	_footstepSounds.AddAudioFile("Assets/sfx_footstep02.wav");
	_footstepSounds.AddAudioFile("Assets/sfx_footstep03.wav");
	_footstepSounds.SetPitchRange({ 0.95f, 1.2f });
	_footstepSounds.SetVolume(0.42f);
}

void MoveSystem::Update(float delta) {
	auto playerView = _registry->view<Transform, SpriteAnimator, PlayerController>();
	auto player = playerView.front();
	auto& playerTransform = _registry->get<Transform>(player);
	auto& playerController = _registry->get<PlayerController>(player);
	auto& animator = _registry->get<SpriteAnimator>(player);

	playerController.passedTime += delta;
	playerController.isGrounded = playerController.isGrounded;

	HandleInput(playerController);

	if (abs(playerController.moveDirection) > 0.1f) {
		animator.flip.x = (playerController.moveDirection < 0.1f);
	}

	if (playerController.isTouchingRight) {
		if (playerController.velocity.x > 0.0f) {
			playerController.velocity.x = 0.0f;
		}
	}
	if (playerController.isTouchingLeft) {
		if (playerController.velocity.x < 0.0f) {
			playerController.velocity.x = 0.0f;
		}
	}
	if (playerController.isTouchingTop) {
		if (playerController.velocity.y > 0.0f) {
			playerController.jumpReleased = true;
		}
	}

	if (ShouldJump(playerController)) {
		playerController.velocity.y = playerController.jumpPower;
		_jumpSound.Play(0);
		_footstepSounds.PlayShuffle();
		playerController.initialAirHorizontalVelocity = playerController.velocity.x;
		playerController.readyToJumpAgain = false;
	}

	if (playerController.isGrounded) {
		if (playerController.moveDirection != 0.0f) {
			if (playerController.moveDirection * playerController.velocity.x < 0.0f) {
				playerController.velocity.x = 0.0f;
			}
			playerController.velocity.x = glm::clamp(playerController.velocity.x + playerController.moveDirection * playerController.groundAcceleration * delta, -playerController.maxHorizontalSpeed, playerController.maxHorizontalSpeed);
			if (animator.curAnimation != &animator.animations.at("Run")) {
				animator.curAnimation = &animator.animations.at("Run");
				animator.curFrame = 0;
				animator.speed = 16.0f;

				// play footstep sound on frames 2 and 6 when the feet hit the ground in the run animation
			}
			else if (animator.curFrame == 2 || animator.curFrame == 6) {
				_footstepSounds.PlayShuffle();
			}
		}
		else {
			playerController.velocity.x -= playerController.velocity.x * playerController.groundDeceleration * delta;
			if (animator.curAnimation != &animator.animations.at("Idle")) {
				animator.curAnimation = &animator.animations.at("Idle");
				animator.curFrame = 0;
				animator.speed = 16.0f;
			}
		}

		if (playerController.velocity.y < 0.0f) {
			playerController.velocity.y = 0.0f;
		}

		if (!playerController.wasGroundedLastFrame) {
			_jumpSound.Play(1);
			_footstepSounds.PlayShuffle();
		}

		playerController.wasGroundedLastFrame = true;
	}
	else {
		if (playerController.wasGroundedLastFrame) {
			playerController.wasGroundedLastFrame = false;
			if (playerController.velocity.y < 1.0f)
				playerController.lastGroundedTime = playerController.passedTime;
		}
		if (animator.curAnimation != &animator.animations.at("Jump")) {
			animator.curAnimation = &animator.animations.at("Jump");
			animator.speed = 0.0f;
		}

		playerController.velocity.x = glm::clamp(playerController.velocity.x + playerController.moveDirection * playerController.airHorizontalAcceleration * delta, -playerController.maxHorizontalSpeed, playerController.maxHorizontalSpeed);
		// Convert horizontal velocity to vertical velocity when going up
		if (playerController.velocity.y > 0.0f && playerController.moveDirection * playerController.initialAirHorizontalVelocity < 0.0f && playerController.moveDirection * playerController.velocity.x < 0.0f) {
			playerController.velocity.y += playerController.airVerticalAcceleration * delta;
		}

		if (playerController.velocity.y > 2.0f) {
			animator.curFrame = 0;
		}
		else if (playerController.velocity.y < -4.5f) {
			animator.curFrame = 2;
		}
		else {
			animator.curFrame = 1;
		}

		if (playerController.jumpReleased || playerController.velocity.y < -0.2f) {
			playerController.velocity.y -= playerController.gravity * delta;
		}
		else {
			playerController.velocity.y -= playerController.jumpHeldGravity * delta;
		}
	}

	playerTransform.position += playerController.velocity * delta;
}

void MoveSystem::HandleInput(PlayerController& pc) {
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_ESCAPE)) {
		ServiceLocator::GetApplication()->Quit();
	}

	pc.moveDirection = 0.0f;

	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_A) ||
		ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_LEFT)) {
		pc.moveDirection -= 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_D) ||
		ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_RIGHT)) {
		pc.moveDirection += 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_W) ||
		ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_UP) ||
		ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_SPACE)) {
		pc.jumpReleased = false;
		pc.jumpPressedTime = pc.passedTime;
	}
	if (ServiceLocator::GetInputManager()->GetKeyUp(GLFW_KEY_W) ||
		ServiceLocator::GetInputManager()->GetKeyUp(GLFW_KEY_UP) ||
		ServiceLocator::GetInputManager()->GetKeyUp(GLFW_KEY_SPACE)) {
		pc.jumpReleased = true;
		pc.readyToJumpAgain = true;
	}
}

bool MoveSystem::ShouldJump(PlayerController& pc) const {
	bool keyPressedInTime = pc.jumpReleased ?
		pc.passedTime - pc.jumpPressedTime < pc.jumpCache1 :
		pc.passedTime - pc.jumpPressedTime < pc.jumpCache2;

	bool coyote = pc.passedTime - pc.lastGroundedTime < pc.coyoteTime;

	return (pc.isGrounded || coyote) && keyPressedInTime && pc.readyToJumpAgain;
}
