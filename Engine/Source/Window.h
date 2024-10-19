#pragma once

#include <glad/glad.h>

struct GLFWwindow;

class Window {
public:
	Window(int width, int height, const char* title);

	bool ShouldClose() const;
	void Update();
	void Close();

	GLFWwindow* GetInternalWindow() const { return _window; }

private:
	static void FramebufferResizeCallback(GLFWwindow* window, GLsizei width, GLsizei height);

	GLFWwindow* _window;
};