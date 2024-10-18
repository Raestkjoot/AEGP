#include "HelloSystem.h"

#include "Logger.h"
#include "ECS/Components/Transform.h"
#include "ServiceLocator.h"
#include "InputManager.h"

#include <GLFW/glfw3.h>

void HelloSystem::Start() {
	// This is the way to get all entities
	// TODO: Might want to make our own function for this too?
	//for (auto entity : _registry->view<entt::entity>()) {

	// TODO: Make our own function for _registry.view<args>().each()
	//for (auto [entity, transform] : _registry->view<Transform>().each()) {

	Logger::Print("Hello, Start()!");
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_F);
}

void HelloSystem::Update() {
	if (ServiceLocator::GetInputManager()->IsKeyDown(GLFW_KEY_F)) {
		Logger::Print("Hello, Update()!");
	}
}

void HelloSystem::End() {
	Logger::Print("Hello, End()!");
}
