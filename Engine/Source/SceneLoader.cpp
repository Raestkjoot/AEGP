#include "SceneLoader.h"

#include "Logger.h"

#include <nlohmann/json.hpp>

#include <fstream>

void SceneLoader::LoadScene(std::string filename) {
	std::ifstream sceneFile(filename);
	nlohmann::json systems = nlohmann::json::parse(sceneFile).at("Systems");
	sceneFile.seekg(0);
	nlohmann::json entities = nlohmann::json::parse(sceneFile).at("Entities");

	for (auto& system : systems) {
		Logger::Print("TODO: Add system {}", system.get<std::string>());
	}

	for (auto& entity : entities) {
		Logger::Print("TODO: Add entity {}", entity.at("Name").get<std::string>());

		nlohmann::json components = entity.at("Components");

		for (auto& component : components) {
			Logger::Print("  TODO: Add component {}", component.at("Name").get<std::string>());
		}
	}
}