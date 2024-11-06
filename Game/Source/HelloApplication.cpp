#include "HelloApplication.h"

#include "Logger.h"
#include "HelloScene.h"
#include "SceneLoader.h"
#include "HelloSystem.h"
#include "SystemFactory.h"

#include <GLFW/glfw3.h>

HelloApplication::HelloApplication() : Application(512, 512, "Hello") { }

void HelloApplication::Initialize() {
	Logger::Print("App: Hello, world!");
	_curScene = new HelloScene();
	
	_systemFactory->RegisterSystem("HelloSystem", []() {return std::make_unique<HelloSystem>(); });

	LoadScene("Assets/HelloScene.json");

	Application::Initialize();
}