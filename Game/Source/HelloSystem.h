#pragma once

#include "ECS/System.h"
#include "Audio.h"

class HelloSystem : public System {
public:
	void Start() override;
	void Update(float delta) override;
	void End() override;

private:
	Audio _audio;
};