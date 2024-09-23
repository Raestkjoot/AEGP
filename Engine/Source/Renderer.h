#pragma once

#include <glad/glad.h>

class Window;

class Renderer {
public:
	Renderer::Renderer();

private:
	Window* _window = nullptr;
};