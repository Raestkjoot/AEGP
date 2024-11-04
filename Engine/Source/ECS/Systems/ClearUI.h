#pragma once

#include "ECS/System.h"

class ClearUI : public System {
public:
	void Update(float delta) override;
};