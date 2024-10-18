#include "Application.h"
#include "Application.h"

#include "Window.h"
#include "Renderer/Renderer.h"
#include "Logger.h"

#include <GLFW/glfw3.h>


static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//_inputManager.KeyCallback(key, action, mods);
	InputManager::GetInstance().KeyCallback(key, action, mods);
}

Application::Application(int width, int height, const char* title)
	: _window(width, height, title), _renderer() {

	glfwSetKeyCallback(_window.GetInternalWindow(), KeyCallback);
}

void Application::Run() {
	InputManager();
	Initialize();

	while (IsRunning()) {
		InputManager::GetInstance().Update();
		_window.Update();

		Update();
	}

	Cleanup();
}

bool Application::IsRunning() const {
	return !_window.ShouldClose();
}
