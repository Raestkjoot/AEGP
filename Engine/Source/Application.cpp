#include "Application.h"

#include "Window.h"
#include "Renderer.h"
#include "Logger.h"

Application::Application(int width, int height, const char* title)
	: _window(width, height, title) {
	_renderer = Renderer();
	Logger::SetLogLevel(Logger::Debug);
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

bool Application::IsRunning() const {
	return !_window.ShouldClose();
}
