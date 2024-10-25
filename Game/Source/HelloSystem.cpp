#include "HelloSystem.h"

#include "Logger.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

#include <fstream>

void HelloSystem::Start() {
	Logger::Print("Hello, Start()!");
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_F);
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_ESCAPE);

	// Read JSON
	std::ifstream f("Engine/Assets/DefaultTextures.json");
	nlohmann::json data = nlohmann::json::parse(f);
	std::string elem0 = data.at("frames").at(0).at("filename").get<std::string>();
	int elem1;
	data.at("frames").at(0).at("frame").at("w").get_to(elem1);
	Logger::Print("File {} has width {}", elem0, elem1);

	// Write JSON
	auto j = R"(
	  {
		"Hello": "World",
		"isAlive": true,
		"pi": 3.14159265
	  }
	)"_json;
	std::ofstream o("output.json");
	o << j.dump(4);
}

void HelloSystem::Update(float delta) {
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_F)) {
		Logger::Print("Hello, Update(delta = {})", delta);
	}

	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_ESCAPE)) {
		ServiceLocator::GetApplication()->Quit();
	}
}

void HelloSystem::End() {
	Logger::Print("Hello, End()!");
}