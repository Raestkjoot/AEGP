#include "TestbedApplication.h"

#include "Logger.h"
#include "Renderer/SpriteRenderPass.h"
#include "ECS/Scene.h"
#include "HelloSystem.h"

TestbedApplication::TestbedApplication() : Application(512, 512, "Hello") {

}

void TestbedApplication::Initialize() {
	Logger::Print("App: Hello, world!");

	std::unique_ptr<SpriteRenderPass> spritePass = std::make_unique<SpriteRenderPass>();
	spritePass->AddSprite();
	_renderer.AddRenderPass(std::move(spritePass));

	std::unique_ptr<HelloSystem> helloSystem = std::make_unique<HelloSystem>();
	_mainScene.AddSystem(std::move(helloSystem));
	_mainScene.CreateEntity();
	_mainScene.Start();
}

void TestbedApplication::Update() {
	
}

void TestbedApplication::Render() {
	Application::Render();
}

void TestbedApplication::Cleanup() {

}