#include "ClearRenderer.h"

#include "Renderer/Renderer.h"

void ClearRenderer::Start() {
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ClearRenderer::Update(float delta) {
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void ClearRenderer::Init(entt::registry* registry) {
	System::Init(registry);
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}
