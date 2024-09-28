#pragma once

#include "RenderPass.h"

#include <glad/glad.h>

#include <vector>
#include <memory>

class Window;

class Renderer {
public:
	Renderer();

	void Render();
    void AddRenderPass(std::unique_ptr<RenderPass> pass);

private:
	Window* _window = nullptr;
    std::vector<std::unique_ptr<RenderPass>> _renderPasses;
};