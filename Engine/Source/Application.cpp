#include "Application.h"

#include "Window.h"
#include "Renderer.h"

#include <iostream>

Application::Application(int width, int height, const char* title)
	: _window(width, height, title) {
	_renderer = Renderer();
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
