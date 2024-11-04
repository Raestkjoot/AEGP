#include "ClearRenderer.h"

#include "Renderer/Renderer.h"

void ClearRenderer::Start() {
	ClearFrame();
}

void ClearRenderer::Update(float delta) {
	ClearFrame();
}

void ClearRenderer::ClearFrame() {
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}