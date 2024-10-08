#pragma once

#include "Window.h"
#include "Renderer/Renderer.h"

class Application {
public:
	Application(int width, int height, const char* title);

	void Run();

protected:
	bool IsRunning() const;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Cleanup() = 0;

protected:
	Window _window;
	Renderer _renderer;
};