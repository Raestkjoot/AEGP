#include "MoveSystem.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "ECS/Components/Transform.h"
#include "Logger.h"

#include <glfw/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

void MoveSystem::Start() {
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_W);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_A);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_S);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_D);

	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_Q);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_E);

	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_Z);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_X);
}

void MoveSystem::Update(float delta) {
	_moveDirection = { 0.0f, 0.0f };
	_rotationDirection = 0.0f;
	_scaleDirection = { 0.0f, 0.0f };

	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_W)) {
		_moveDirection.y += 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_S)) {
		_moveDirection.y -= 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_A)) {
		_moveDirection.x -= 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_D)) {
		_moveDirection.x += 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_Q)) {
		_rotationDirection += 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_E)) {
		_rotationDirection -= 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_Z)) {
		_scaleDirection -= 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_X)) {
		_scaleDirection += 1.0f;
	}

	if (glm::length2(_moveDirection) > 0.01f || 
		_rotationDirection != 0.0f ||
		glm::length2(_scaleDirection) > 0.01f) {

		auto view = _registry->view<Transform>();

		for (auto [entity, transform] : view.each()) {
			transform.position += _moveDirection * _moveSpeed * delta;
			transform.rotation += _rotationDirection * _rotationSpeed * delta;
			transform.scale += _scaleDirection * _scaleSpeed * delta;
		}
	}
}