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

	for (auto& entityData : entities) {
		auto entity = scene.CreateEntity();

		nlohmann::json components = entityData.at("Components");

		for (auto& component : components) {
			_componentFactory->GetComponent(component.at("Name").get<std::string>(), scene, entity);
		}
	}

	return scene;
}