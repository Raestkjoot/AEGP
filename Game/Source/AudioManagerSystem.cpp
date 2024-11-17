#include "AudioManagerSystem.h"

#include "Logger.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

#include <fstream>

void AudioManagerSystem::Start() {
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_M);

	_audio.Load("Assets/Track03.wav");
	_audio.Loop(true);
}

void AudioManagerSystem::Update(float delta) {
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_M)) {
		_audio.PlayPause();
	}
}