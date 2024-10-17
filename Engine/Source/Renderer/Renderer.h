#pragma once

#include <glad/glad.h>

#include <vector>
#include <memory>

class Window;

class Renderer {
public:
	Renderer();

private:
	Window* _window = nullptr;
};