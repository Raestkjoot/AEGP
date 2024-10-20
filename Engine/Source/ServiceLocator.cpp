#include "ServiceLocator.h"

InputManager* ServiceLocator::_inputManager = nullptr;
Application* ServiceLocator::_application = nullptr;

void ServiceLocator::SetInputManager(InputManager* inputManager) {
	assert(_inputManager == nullptr);
	_inputManager = inputManager;
}

void ServiceLocator::SetApplication(Application* application) {
	assert(_application == nullptr);
	_application = application;
}