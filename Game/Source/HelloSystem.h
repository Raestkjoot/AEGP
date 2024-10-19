#pragma once

#include "ECS/System.h"

class HelloSystem : public System {
public:
	void Start() override;
	void Update(float delta) override;
	void End() override;
};