#include "MoveSystem.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "Application.h"
#include "PlayerControllerTag.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"
#include "Logger.h"

#include <glfw/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>

void MoveSystem::Start() {
	
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_A);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_D);
	//ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_W);
	//ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_S);

	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_ESCAPE);
}

void MoveSystem::Update(float delta) {
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_ESCAPE)) {
		ServiceLocator::GetApplication()->Quit();
	}
	
	_moveDirection = { 0.0f, -1.0f};

	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_A)) {
		_moveDirection.x -= 1.0f;
	}
	if (ServiceLocator::GetInputManager()->GetKey(GLFW_KEY_D)) {
		_moveDirection.x += 1.0f;
	}

	if (glm::length2(_moveDirection) > 0.01f) {
		auto playerView = _registry->view<Transform, Sprite, PlayerControllerTag>();
		auto player = playerView.front();
		auto& playerTransform = _registry->get<Transform>(player);

		playerTransform.position += _moveDirection * _moveSpeed * delta;
	}
}