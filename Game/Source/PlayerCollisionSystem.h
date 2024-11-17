#pragma once

#include "ECS/System.h"

class PlayerCollisionSystem : public System {
	void Update(float delta) override;
};