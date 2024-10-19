#pragma once

#include <entt/entt.hpp>

class System {
	friend class Scene;

public:
	virtual void Start();
	virtual void Update(float delta);
	virtual void End();

protected:
	virtual void Init(entt::registry* registry);

	entt::registry* _registry = nullptr;
};