#include "SceneLoader.h"

#include "Logger.h"
#include "SystemFactory.h"
#include "ComponentFactory.h"
#include "ECS/Scene.h"

#include <nlohmann/json.hpp>

#include <fstream>

SceneLoader::SceneLoader(SystemFactory* systemFactory, ComponentFactory* componentFactory) :
	_systemFactory(systemFactory), _componentFactory(componentFactory) {}

Scene SceneLoader::LoadScene(std::string filename) {
	Scene scene;

	std::ifstream sceneFile(filename);
	nlohmann::json systems = nlohmann::json::parse(sceneFile).at("Systems");
	sceneFile.seekg(0);
	nlohmann::json entities = nlohmann::json::parse(sceneFile).at("Entities");

	for (auto& system : systems) {
		scene.AddSystem(
			_systemFactory->GetSystem(system.get<std::string>())
		);
	}

	for (auto& entity : entities) {
		Logger::Print("TODO: Add entity {}", entity.at("Name").get<std::string>());

		nlohmann::json components = entity.at("Components");

		for (auto& component : components) {
			_componentFactory->GetComponent(component.at("Name").get<std::string>());
		}
	}

	return scene;
}