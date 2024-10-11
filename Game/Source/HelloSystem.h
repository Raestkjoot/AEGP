#pragma once

#include "ECS/System.h"

class HelloSystem : public System {
public:
	void Start() override;
	void Update() override;
	void End() override;
};