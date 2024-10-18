#include "ServiceLocator.h"

InputManager* ServiceLocator::_inputManager = nullptr;

void ServiceLocator::SetInputManager(InputManager* inputManager) {
	assert(_inputManager == nullptr);
	_inputManager = inputManager;
}