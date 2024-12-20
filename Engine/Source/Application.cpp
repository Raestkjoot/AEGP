#include "Application.h"

#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioEngine.h"
#include "Input/InputManager.h"
#include "Scene/SceneLoader.h"
#include "Scene/Scene.h"
#include "Scene/SystemFactory.h"
#include "Scene/ComponentFactory.h"
#include "Utils/ServiceLocator.h"
#include "Utils/Timer.h"
#include "Utils/Logger.h"

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
	_audioEngine(new AudioEngine()),
	_inputManager(new InputManager()),
	_systemFactory(new SystemFactory()),
	_componentFactory(new ComponentFactory()),
	_sceneLoader(new SceneLoader(_systemFactory, _componentFactory)) {

	ServiceLocator::SetAudioEngine(_audioEngine);
	ServiceLocator::SetInputManager(_inputManager);
	ServiceLocator::SetApplication(this);

	glfwSetKeyCallback(_window->GetInternalWindow(), KeyCallback);

	// Initialize ImGUI
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable docking imgui windows
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

		_curScene->Update(updateTimer.Tick());
	}

	Cleanup();
}

void Application::LoadScene(const std::string& sceneName) {
	_curScene = _sceneLoader->LoadScene(sceneName);
}

bool Application::IsRunning() const {
	return !_window->ShouldClose();
}

void Application::Initialize() {
	_curScene->Start();
}

void Application::Cleanup() {
	_curScene->End();

	delete _inputManager;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete _audioEngine;
	delete _renderer;
	delete _window;
}

void Application::Quit() {
	_window->Close();
}