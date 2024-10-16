#include "HelloSystem.h"

#include "Logger.h"
#include "ServiceLocator.h"
#include "InputManager.h"

#include <GLFW/glfw3.h>

void HelloSystem::Start() {
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