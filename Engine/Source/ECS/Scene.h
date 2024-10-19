#pragma once

#include "System.h"

#include <entt/entt.hpp>

#include <memory>
#include <vector>
#include <typeinfo>

class Scene {
public:
	virtual void Initialize() = 0;

	void Start();
	void Update();
	void End();

	entt::entity CreateEntity();
	void AddSystem(std::unique_ptr<System> system);

	template<typename T, typename... Args>
	void AddComponent(entt::entity entity, Args... args) {
		_registry.emplace<T>(entity, std::forward<Args>(args)...);
	}

private:
	entt::registry _registry;
	std::vector< std::unique_ptr<System> > _systems;
};