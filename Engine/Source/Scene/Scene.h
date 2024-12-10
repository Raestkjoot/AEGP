#pragma once

#include "Systems/System.h"
#include "Utils/Logger.h"

#include <entt/entt.hpp>

#include <memory>
#include <vector>
#include <typeinfo>

class Scene {
public:
	void Start();
	void Update(float delta);
	void End();

	entt::entity CreateEntity();
	void AddSystem(std::unique_ptr<System> system);

	template<typename T, typename... Args>
	void AddComponent(entt::entity entity, Args... args) {
		_registry.emplace<T>(entity, std::forward<Args>(args)...);
	}

	template<typename T>
	T* GetComponent(entt::entity entity) {
		return &_registry.get<T>(entity);
	}

private:
	friend class SceneLoader;

	entt::registry _registry;
	std::vector< std::unique_ptr<System> > _systems;
};