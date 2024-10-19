#include "HelloSystem.h"

#include "Logger.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "Application.h"

#include <GLFW/glfw3.h>

void HelloSystem::Start() {
	Logger::Print("Hello, Start()!");
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_F);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_ESCAPE);
}

void HelloSystem::Update() {
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_F)) {
		Logger::Print("Hello, Update()!");
	}

	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_ESCAPE)) {
		ServiceLocator::GetApplication()->Quit();
	}
}

void HelloSystem::End() {
	Logger::Print("Hello, End()!");
}