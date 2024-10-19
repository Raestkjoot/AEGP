#include "Application.h"

#include "Window.h"
#include "Renderer/Renderer.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "ECS/Scene.h"
#include "Timer.h"

#include <GLFW/glfw3.h>

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	ServiceLocator::GetInputManager()->KeyCallback(key, action, mods);
}

Application::Application(int width, int height, const char* title) : 
	_window(new Window(width, height, title)), 
	_renderer(new Renderer()), 
	_inputManager(new InputManager()) {

	ServiceLocator::SetInputManager(_inputManager);
	ServiceLocator::SetApplication(this);

	glfwSetKeyCallback(_window->GetInternalWindow(), KeyCallback);
}

void Application::Run() {
	Initialize();

	Timer updateTimer;

	while (IsRunning()) {
		ServiceLocator::GetInputManager()->Update();
		_window->Update();

		Update(updateTimer.GetDeltaTime());
	}

	Cleanup();
}

bool Application::IsRunning() const {
	return !_window->ShouldClose();
}

void Application::Initialize() {
	_curScene->Initialize();
	_curScene->Start();
}

void Application::Update(float delta) {
	_curScene->Update(delta);
}

void Application::Cleanup() {
	_curScene->End();

	delete _curScene;
	delete _inputManager;
	delete _renderer;
	delete _window;
}

void Application::Quit() {
	_window->Close();
}