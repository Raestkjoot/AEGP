#pragma once

#include "Systems/System.h"
#include "Audio/AudioArray.h"

#include "glm/glm.hpp"

class PlayerController;

class MoveSystem : public System {
public:
	void Start() override;
	void Update(float delta) override;

private:
	void HandleInput(PlayerController&);
	bool ShouldJump(PlayerController&) const;

	AudioArray _jumpSound;
	AudioArray _footstepSounds;
};