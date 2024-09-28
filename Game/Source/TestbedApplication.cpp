#include "TestbedApplication.h"

#include "Logger.h"
#include "Renderer/SpriteRenderPass.h"

TestbedApplication::TestbedApplication() : Application(512, 512, "Hello") {

}

void TestbedApplication::Initialize() {
	Logger::Print("Hello, world!");

	std::unique_ptr<SpriteRenderPass> spritePass = std::make_unique<SpriteRenderPass>();
	spritePass->AddSprite();
	_renderer.AddRenderPass(std::move(spritePass));
}

void TestbedApplication::Update() {
	
}

void TestbedApplication::Render() {
	Application::Render();
}

void TestbedApplication::Cleanup() {

}