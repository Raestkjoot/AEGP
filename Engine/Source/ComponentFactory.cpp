#include "ComponentFactory.h"

#include "Logger.h"

void ComponentFactory::GetComponent(const std::string& name, Scene& scene, entt::entity e) {
	Logger::Print("Get Component {}", name);

	auto component = _componentMap.find(name);
	if (component != _componentMap.end()) {
		component->second(scene, e);
	} else {
		Logger::PrintError("ComponentFactory::GetComponent: '{}' not found", name);
	}
}

void ComponentFactory::RegisterComponent(const std::string& name, std::function<void(Scene&, entt::entity)> builder) {
	_componentMap[name] = builder;
}
