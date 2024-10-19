#pragma once

#include "cassert"

class InputManager;
class Application;

class ServiceLocator {
public:
	static InputManager* GetInputManager() {
		assert(_inputManager != nullptr);
		return _inputManager;
	}
	static void SetInputManager(InputManager* inputManager);

	static Application* GetApplication() {
		assert(_application != nullptr);
		return _application;
	}
	static void SetApplication(Application* application);

private:
	static InputManager* _inputManager;
	static Application* _application;
};