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
	_mainScene.Update();
}

void TestbedApplication::Cleanup() {

}