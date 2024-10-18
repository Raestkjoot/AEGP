#include "Application.h"
#include "Application.h"

#include "Window.h"
#include "Renderer/Renderer.h"
#include "Logger.h"
#include "ServiceLocator.h"
#include "InputManager.h"

#include <GLFW/glfw3.h>


static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	ServiceLocator::GetInputManager()->KeyCallback(key, action, mods);
}

Application::Application(int width, int height, const char* title)
	: _window(width, height, title), _renderer(), _inputManager(new InputManager()) {

	ServiceLocator::SetInputManager(_inputManager);
	glfwSetKeyCallback(_window.GetInternalWindow(), KeyCallback);
}

void Application::Run() {
	Initialize();

	while (IsRunning()) {
		ServiceLocator::GetInputManager()->Update();
		_window.Update();

		Update();
	}

	Cleanup();
}

bool Application::IsRunning() const {
	return !_window.ShouldClose();
}
