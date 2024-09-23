#pragma once

#include <glad/glad.h>

class Window;

class Renderer {
public:
	Renderer::Renderer();

	void Render();

private:
	Window* _window = nullptr;
};