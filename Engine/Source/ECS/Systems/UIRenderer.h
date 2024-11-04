#pragma once

#include "ECS/System.h"

class UIRenderer : public System {
public:
	void Update(float delta) override;
};