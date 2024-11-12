#pragma once

#include "ECS/System.h"

class CollisionSystem : public System {
	void Update(float delta) override;
};