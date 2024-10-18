#pragma once

#include <glad/glad.h>

struct GLFWwindow;

class Window {
public:
	Window(int width, int height, const char* title);

	bool ShouldClose() const;
	void Update();

	GLFWwindow* GetInternalWindow() const { return _window; }

private:
	// TODO: move some of the input handling to an input manager
	void ProcessInput();
	static void FramebufferResizeCallback(GLFWwindow* window, GLsizei width, GLsizei height);

	GLFWwindow* _window;
};