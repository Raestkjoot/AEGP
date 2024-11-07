#pragma once

#include "Logger.h"
#include "ECS/Scene.h"

#include <entt/entt.hpp>

#include <string>
#include <map>

class ComponentFactory {
public:
	void GetComponent(const std::string& name, Scene& scene, entt::entity e);
	void RegisterComponent(const std::string& name, std::function<void(Scene&, entt::entity)> builder);

private:
	std::map<std::string, std::function<void(Scene&, entt::entity)>> _componentMap;
};