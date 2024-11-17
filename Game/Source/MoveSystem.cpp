#include "MoveSystem.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "Application.h"
#include "PlayerController.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"
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
}

void MoveSystem::Update(float delta) {
	auto playerView = _registry->view<Transform, Sprite, PlayerController>();
	auto player = playerView.front();
	auto& playerTransform = _registry->get<Transform>(player);
	auto& playerController = _registry->get<PlayerController>(player);

	HandleInput(playerController.isGrounded);

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

	if (playerController.isGrounded) {
		if (_moveDirection != 0.0f) {
			_velocity.x = glm::clamp(_velocity.x + _moveDirection * _groundMoveAcceleration * delta, -_maxVelocity, _maxVelocity);
		} else {
			_velocity.x -= _velocity.x * _groundStopAcceleration * delta;
		}
		
		if (_jump) {
			_velocity.y = _jumpPower;
		} else if (_velocity.y < 0.0f) {
			_velocity.y = 0.0f;
		}
	} else {
		_velocity.x = glm::clamp(_velocity.x + _moveDirection * _airMoveAcceleration * delta, -_maxVelocity, _maxVelocity);
		if (_jumpReleased) {
			_velocity.y -= _jumpReleasedGravity * delta;
		} else {
			_velocity.y -= _jumpHeldGravity * delta;
		}
	}

	playerTransform.position += _velocity * delta;
}

void MoveSystem::HandleInput(bool isGrounded) {
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
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_W) ||
		ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_UP)) {
		if (_jumpReleased && isGrounded) {
			_jump = true;
			_jumpReleased = false;
		}
	}
	if (ServiceLocator::GetInputManager()->GetKeyUp(GLFW_KEY_W) ||
		ServiceLocator::GetInputManager()->GetKeyUp(GLFW_KEY_UP)) {
		_jumpReleased = true;
	}
}
