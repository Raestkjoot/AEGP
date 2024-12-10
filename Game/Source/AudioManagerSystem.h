#pragma once

#include "Systems/System.h"
#include "Audio/Audio.h"

class AudioManagerSystem : public System {
public:
	void Start() override;
	void Update(float delta) override;

private:
	Audio _audio;
};