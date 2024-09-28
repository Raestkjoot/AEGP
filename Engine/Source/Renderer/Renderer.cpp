#include "Renderer.h"

#include "Window.h"
#include "Logger.h"
#include "SpriteRenderPass.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderer::Renderer() {
	// Initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Logger::PrintError("Failed to initialize GLAD");
		return;
	}
}

void Renderer::Render() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto& pass : _renderPasses) {
		pass->Render();
	}
}

void Renderer::AddRenderPass(std::unique_ptr<RenderPass> pass)
{
	pass->Init();
	_renderPasses.push_back(std::move(pass));
}
