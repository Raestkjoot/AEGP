#pragma once

#include "cassert"

class InputManager;

class ServiceLocator {
public:
	static InputManager* GetInputManager() {
		assert(_inputManager != nullptr);
		return _inputManager;
	}
	static void SetInputManager(InputManager* inputManager);

private:
	static InputManager* _inputManager;
};