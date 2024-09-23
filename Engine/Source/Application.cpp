#include "Application.h"

#include <glad\glad.h>

Application::Application(int width, int height, const char* title) {
	//TODO: Initialize window
}

void Application::Run() {
	Initialize();

	while (IsRunning()) {
		Update();
		Render();
	}

	Cleanup();
}

bool Application::IsRunning() const {
	return _isRunning;
}
