#pragma once

#include "Systems/System.h"

class PlayerCollisionSystem : public System {
	void Update(float delta) override;
};