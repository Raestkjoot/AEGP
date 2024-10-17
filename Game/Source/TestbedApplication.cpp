#include "TestbedApplication.h"

#include "Logger.h"
#include "ECS/Scene.h"
#include "ECS/Components/Transform.h"
#include "HelloSystem.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Components/Sprite.h"

#include <GLFW/glfw3.h>

TestbedApplication::TestbedApplication() : Application(512, 512, "Hello") {

}

void TestbedApplication::Initialize() {
	Logger::Print("App: Hello, world!");

	_mainScene.AddSystem(std::make_unique<HelloSystem>());
	_mainScene.AddSystem(std::make_unique<ClearRenderer>());
	_mainScene.AddSystem(std::make_unique<SpriteRenderer>());

	auto entity = _mainScene.CreateEntity();
	_mainScene.AddComponent<Transform>(entity);
	_mainScene.AddComponent<Sprite>(entity);

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

void TestbedApplication::Cleanup() {

}