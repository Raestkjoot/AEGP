#include "Renderer.h"

#include "Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderer::Renderer() {
	// Initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Logger::PrintError("Failed to initialize GLAD");
		return;
	}
}