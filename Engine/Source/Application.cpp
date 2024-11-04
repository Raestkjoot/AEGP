#include "Application.h"

#include "Window.h"
#include "Renderer/Renderer.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "ECS/Scene.h"
#include "Timer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
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

	// Initialize ImGUI
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_window->GetInternalWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 410");
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

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete _renderer;
	delete _window;

}

void Application::Quit() {
	_window->Close();
}