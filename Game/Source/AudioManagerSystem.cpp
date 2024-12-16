#include "AudioManagerSystem.h"

#include "Utils/Logger.h"
#include "Utils/ServiceLocator.h"
#include "Input/InputManager.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <nlohmann/json.hpp>

#include <fstream>

void AudioManagerSystem::Start() {
	ServiceLocator::GetInputManager()->ListenToKey(GLFW_KEY_M);

	_audio.Load("Assets/Xeph-Loop.mp3");
	_audio.SetVolume(0.4f);
	_audio.Loop(true);
	_audio.Play();
}

void AudioManagerSystem::Update(float delta) {
	if (ServiceLocator::GetInputManager()->GetKeyDown(GLFW_KEY_M)) {
		_audio.PlayPause();
	}
}