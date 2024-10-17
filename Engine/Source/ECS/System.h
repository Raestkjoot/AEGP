#pragma once

#include <entt/entt.hpp>

class System {
	friend class Scene;

public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

protected:
	virtual void Init(entt::registry* registry);

	entt::registry* _registry = nullptr;
};