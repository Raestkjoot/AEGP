#include "SceneLoader.h"

#include "Logger.h"
#include "SystemFactory.h"
#include "ComponentFactory.h"
#include "ECS/Scene.h"

#include <nlohmann/json.hpp>

#include <fstream>

SceneLoader::SceneLoader(SystemFactory* systemFactory, ComponentFactory* componentFactory) :
	_systemFactory(systemFactory), _componentFactory(componentFactory) {}

Scene* SceneLoader::LoadScene(std::string filename) {
	Scene* scene = new Scene();

	std::ifstream sceneFile(filename);
	nlohmann::json systems = nlohmann::json::parse(sceneFile).at("Systems");
	sceneFile.seekg(0);
	nlohmann::json entities = nlohmann::json::parse(sceneFile).at("Entities");

	for (auto& systemName : systems) {
		auto system = _systemFactory->GetSystem(systemName.get<std::string>());
		scene->AddSystem(std::move(system));
	}

	for (auto& entityData : entities) {
		auto entity = scene->CreateEntity();

		nlohmann::json components = entityData.at("Components");

		for (auto& component : components) {
			auto name = component.at("Name").get<std::string>();
			auto args = component.contains("Arguments") ? component.at("Arguments") : nlohmann::json();

			_componentFactory->GetComponent(name, args, scene, entity);
		}
	}

	return scene;
}