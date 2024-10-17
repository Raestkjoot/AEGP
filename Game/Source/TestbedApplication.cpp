#include "TestbedApplication.h"

#include "Logger.h"
#include "Renderer/SpriteRenderPass.h"
#include "ECS/Scene.h"
#include "ECS/Components/Transform.h"
#include "HelloSystem.h"
#include "ECS/Systems/UpdateSpriteTransforms.h"

#include <GLFW/glfw3.h>

TestbedApplication::TestbedApplication() : Application(512, 512, "Hello") {

}

void TestbedApplication::Initialize() {
	Logger::Print("App: Hello, world!");

	std::unique_ptr<SpriteRenderPass> spritePass = std::make_unique<SpriteRenderPass>();
	spritePass->AddSprite();
	_renderer.AddRenderPass(std::move(spritePass));

	_mainScene.AddSystem(std::move(std::make_unique<HelloSystem>()));
	_mainScene.AddSystem(std::make_unique<UpdateSpriteTransforms>());
	auto entity = _mainScene.CreateEntity();
	_mainScene.AddComponent<Transform>(entity);
	_mainScene.Start();
}

void TestbedApplication::Update() {
	if (glfwGetKey(_window.GetInternalWindow(), GLFW_KEY_F) == GLFW_PRESS) {
		if (_testButtonReleased) {
			_testButtonReleased = false;
			_testButtonPressed = true;
		}
	}
	if (glfwGetKey(_window.GetInternalWindow(), GLFW_KEY_F) == GLFW_RELEASE) {
		if (!_testButtonReleased) {
			_testButtonReleased = true;
			_testButtonPressed = false;
		}
	}

	if (_testButtonPressed) {
		_mainScene.Update();
		_testButtonPressed = false;
	}
}

void TestbedApplication::Render() {
	Application::Render();
}

void TestbedApplication::Cleanup() {

}