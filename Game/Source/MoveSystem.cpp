#include "MoveSystem.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "PlayerControllerTag.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"
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

	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_I);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_O);
}

void MoveSystem::Update(float delta) {
	_moveDirection = { 0.0f, 0.0f };
	_rotationDirection = 0.0f;
	_scaleDirection = { 0.0f, 0.0f };
	_zoomDirection = 0.0f;

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
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_I)) {
		_zoomDirection += 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_O)) {
		_zoomDirection -= 1.0f;
	}

	if (glm::length2(_moveDirection) > 0.01f || 
		_rotationDirection != 0.0f ||
		glm::length2(_scaleDirection) > 0.01f ||
		_zoomDirection != 0.0f) {

		auto playerView = _registry->view<Transform, Sprite, PlayerControllerTag>();
		auto cameraView = _registry->view<Camera2D>();

		auto player = playerView.front();
		auto camera = cameraView.front();

		auto& playerTransform = _registry->get<Transform>(player);

		playerTransform.position += _moveDirection * _moveSpeed * delta;
		playerTransform.rotation += _rotationDirection * _rotationSpeed * delta;
		playerTransform.scale += _scaleDirection * _scaleSpeed * delta;

		if (glm::abs(_moveDirection.x) > 0.00f) {
			auto& playerSprite = _registry->get<Sprite>(player);
			playerSprite.flip.x = (_moveDirection.x < 0.1f);
		}

		auto& cameraCamera = _registry->get<Camera2D>(camera);
		cameraCamera.position = playerTransform.position;
		//cameraCamera.rotation = playerTransform.rotation;
		cameraCamera.zoom += _zoomDirection * _zoomSpeed * delta;
	}
}