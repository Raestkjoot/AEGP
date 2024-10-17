#pragma once

#include "ECS/System.h"

class UpdateSpriteTransforms : public System {
public:
	void Start() override;
	void Update() override;
	void End() override;

private:
	void Init(entt::registry* registry) override;

	int _testValue = 0;
};