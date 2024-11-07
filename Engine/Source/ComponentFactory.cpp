#include "ComponentFactory.h"

#include "Logger.h"

void ComponentFactory::GetComponent(const std::string& name, nlohmann::json& args, Scene* scene, entt::entity e) {
	auto component = _componentMap.find(name);

	if (component != _componentMap.end()) {
		component->second(scene, e, args);
	} else {
		Logger::PrintError("ComponentFactory::GetComponent: '{}' not found", name);
	}
}

void ComponentFactory::RegisterComponent(const std::string& name, std::function<void(Scene*, entt::entity, nlohmann::json& args)> builder) {
	_componentMap[name] = builder;
}
