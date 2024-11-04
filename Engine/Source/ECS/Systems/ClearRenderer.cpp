#include "ClearRenderer.h"

#include "Renderer/Renderer.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void ClearRenderer::Start() {
	ClearFrame();
}

void ClearRenderer::Update(float delta) {
	ClearFrame();
}

void ClearRenderer::Init(entt::registry* registry) {
	System::Init(registry);
}

void ClearRenderer::ClearFrame() {
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	//ImGui_ImplOpenGL3_NewFrame();
	//ImGui_ImplGlfw_NewFrame();
	//ImGui::NewFrame();
}