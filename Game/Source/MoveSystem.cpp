#include "MoveSystem.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "Application.h"
#include "PlayerController.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/SpriteAnimator.h"
#include "ECS/Components/Camera2D.h"
#include "ECS/Components/Collider_Dynamic.h"
#include "Logger.h"

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

	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_ESCAPE);

	_jumpSounds.AddAudioFile("Assets/Voice.wav");
	_jumpSounds.AddAudioFile("Assets/Voice2.wav");
	_jumpSounds.SetPitchRange({ 1.0f, 1.2f });


	auto playerView = _registry->view<Transform, Sprite, PlayerController>();
	auto player = playerView.front();

	auto& animator = _registry->emplace<SpriteAnimator>(player);
	animator.animations["Idle"] = ServiceLocator::GetSpriteRenderer()->GetSpriteAnim("Idle");
	animator.animations["Run"] = ServiceLocator::GetSpriteRenderer()->GetSpriteAnim("Run");
	animator.animations["Jump"] = ServiceLocator::GetSpriteRenderer()->GetSpriteAnim("Jump");
	animator.curAnimation = &animator.animations.at("Idle");
	animator.speed = 16.f;

	auto& pContrl = _registry->get<PlayerController>(player);
	pContrl.offset = glm::vec2(0.0f, 0.0f);
}

void MoveSystem::Update(float delta) {
	auto playerView = _registry->view<Transform, SpriteAnimator, PlayerController>();
	auto player = playerView.front();
	auto& playerTransform = _registry->get<Transform>(player);
	auto& playerController = _registry->get<PlayerController>(player);
	auto& animator = _registry->get<SpriteAnimator>(player);

	_passedTime += delta;
	_isGrounded = playerController.isGrounded;

	HandleInput();

	if (abs(_moveDirection) > 0.1f) {
		animator.flip.x = (_moveDirection < 0.1f);
	}

	if (playerController.isTouchingRight) {
		if (_velocity.x > 0.0f) {
			_velocity.x = 0.0f;
		}
	}
	if (playerController.isTouchingLeft) {
		if (_velocity.x < 0.0f) {
			_velocity.x = 0.0f;
		}
	}

	if (ShouldJump()) {
		_velocity.y = _jumpPower;
		_jumpSounds.PlayRandom();
	}

	if (_isGrounded) {
		if (_moveDirection != 0.0f) {
			_velocity.x = glm::clamp(_velocity.x + _moveDirection * _groundAcceleration * delta, -_maxHorizontalSpeed, _maxHorizontalSpeed);
			if (animator.curAnimation != &animator.animations.at("Run")) {
				animator.curAnimation = &animator.animations.at("Run");
				animator.curFrame = 0;
				animator.speed = 16.0f;
			}
		} else {
			_velocity.x -= _velocity.x * _groundDeceleration * delta;
			if (animator.curAnimation != &animator.animations.at("Idle")) {
				animator.curAnimation = &animator.animations.at("Idle");
				animator.curFrame = 0;
				animator.speed = 16.0f;
			}
		}
		
		if (_velocity.y < 0.0f) {
			_velocity.y = 0.0f;
		}

		_wasGroundedLastFrame = true;
	} else {
		if (_wasGroundedLastFrame) {
			_wasGroundedLastFrame = false;
			if (_velocity.y < 1.0f)
				_lastGroundedTime = _passedTime;
		}
		if (animator.curAnimation != &animator.animations.at("Jump")) {
			animator.curAnimation = &animator.animations.at("Jump");
			animator.speed = 0.0f;
		}

		_velocity.x = glm::clamp(_velocity.x + _moveDirection * _airHorizontalAcceleration * delta, -_maxHorizontalSpeed, _maxHorizontalSpeed);
		if (_velocity.y < 0.0f && _moveDirection * _velocity.x < 0.0f) {
			_velocity.y += _moveDirection * _airHorizontalAcceleration * delta;
		}

		if (_velocity.y > 2.0f) {
			animator.curFrame = 0;
		} else if (_velocity.y < -4.5f) {
			animator.curFrame = 2;
		} else {
			animator.curFrame = 1;
		}

		if (_jumpReleased || _velocity.y < 0.0f) {
			_velocity.y -= _gravity * delta;
		} else {
			_velocity.y -= _jumpHeldGravity * delta;
		}
	}

	playerTransform.position += _velocity * delta;
}

void MoveSystem::HandleInput() {
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_ESCAPE)) {
		ServiceLocator::GetApplication()->Quit();
	}

	_moveDirection = 0.0f;
	_jump = false;

	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_A) ||
		ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_LEFT)) {
		_moveDirection -= 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_D) ||
		ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_RIGHT)) {
		_moveDirection += 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_W) ||
		ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_UP)) {
		_jumpReleased = false;
		_jumpPressedTime = _passedTime;
	}
	if (ServiceLocator::GetInputManager()->GetKeyUp(GLFW_KEY_W) ||
		ServiceLocator::GetInputManager()->GetKeyUp(GLFW_KEY_UP)) {
		_jumpReleased = true;
	}
}

bool MoveSystem::ShouldJump() {
	bool keyPressedInTime = _jumpReleased ?
		_passedTime - _jumpPressedTime < _jumpCache1 :
		_passedTime - _jumpPressedTime < _jumpCache2;

	bool coyote = _passedTime - _lastGroundedTime < _coyoteTime;

	return (_isGrounded || coyote) && keyPressedInTime;
}
