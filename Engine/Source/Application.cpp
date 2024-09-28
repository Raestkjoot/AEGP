#include "Application.h"

#include "Window.h"
#include "Renderer/Renderer.h"
#include "Logger.h"

Application::Application(int width, int height, const char* title)
	: _window(width, height, title), _renderer() {
}

void Application::Run() {
	Initialize();

	while (IsRunning()) {
		_window.Update();

		// TODO
		Update();
		Render();
	}

	Cleanup();
}

void Application::Render() {
	_renderer.Render();
}

bool Application::IsRunning() const {
	return !_window.ShouldClose();
}
