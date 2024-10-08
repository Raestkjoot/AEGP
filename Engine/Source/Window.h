#pragma once

// TODO: glad probably shouldn't be included in this header
#include <glad/glad.h>

struct GLFWwindow;

class Window {
public:
	Window(int width, int height, const char* title);

	bool ShouldClose() const;
	void Update();

private:
	// TODO: move some of the input handling to an input manager
	void ProcessInput();
	static void FramebufferResizeCallback(GLFWwindow* window, GLsizei width, GLsizei height);

	GLFWwindow* _window;
};