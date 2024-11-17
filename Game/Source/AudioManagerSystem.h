#pragma once

#include "ECS/System.h"
#include "Audio.h"

class AudioManagerSystem : public System {
public:
	void Start() override;
	void Update(float delta) override;

private:
	Audio _audio;
};