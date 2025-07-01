#include "Window.h"

#include "Utils/Logger.h"

#include <GLFW/glfw3.h>

Window::Window(int width, int height, const char* title) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// Remove titlebar
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	_window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (_window == NULL) {
		Logger::PrintError("Failed to create GLFW window");
		return;
	}

	// Center window
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwSetWindowPos(_window, 
		(mode->width / 2) - (width / 2), 
		(mode->height / 2) - (height / 2));

	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, FramebufferResizeCallback);
}

bool Window::ShouldClose() const {
	return glfwWindowShouldClose(_window);
}

void Window::Update() {
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

void Window::Close() {
	glfwSetWindowShouldClose(_window, true);
}

void Window::FramebufferResizeCallback(GLFWwindow* window, GLsizei width, GLsizei height) {
	// When the window changes dimensions, we make sure to adjust the viewport to match
	glViewport(0, 0, width, height);
}