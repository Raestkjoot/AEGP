#pragma once

#include "System.h"

#include "entt/entt.hpp"

#include <memory>
#include <vector>

class Scene {
public:
	void Start();
	void Update();
	void End();

	entt::entity CreateEntity();
	void AddComponent();
	void AddSystem(std::unique_ptr<System> system);

private:
	entt::registry _registry;
	std::vector< std::unique_ptr<System> > _systems;
};