#pragma once

#include "Logger.h"
#include "ECS/Scene.h"

#include <entt/entt.hpp>
#include "nlohmann/json.hpp"

#include <string>
#include <map>

class ComponentFactory {
public:
	void GetComponent(const std::string& name, nlohmann::json& args, Scene* scene, entt::entity e);
	void RegisterComponent(const std::string& name, std::function<void(Scene*, entt::entity, nlohmann::json&)> builder);

private:
	std::map<std::string, std::function<void(Scene*, entt::entity, nlohmann::json&)>> _componentMap;
};