#include "UIRenderer.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"

void UIRenderer::Update(float delta) {
	ImGui::Begin("Hello, world!");
	ImGui::Text("Here is some text for ImGUI");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}