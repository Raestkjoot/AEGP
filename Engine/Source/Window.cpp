#include "Window.h"

#include <GLFW/glfw3.h>

#include <iostream>

Window::Window(int width, int height, const char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return;
	}

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, FramebufferResizeCallback);
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(_window);
}

void Window::Update() {
	ProcessInput();
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void Window::ProcessInput() {
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);
}

void Window::FramebufferResizeCallback(GLFWwindow* window, GLsizei width, GLsizei height) {
	// When the window changes dimensions, we make sure to adjust the viewport to match
	glViewport(0, 0, width, height);
}
