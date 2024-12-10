#include "ServiceLocator.h"

InputManager* ServiceLocator::_inputManager = nullptr;
Application* ServiceLocator::_application = nullptr;
AudioEngine* ServiceLocator::_audioEngine = nullptr;
SpriteRenderer* ServiceLocator::_spriteRenderer = nullptr;

void ServiceLocator::SetInputManager(InputManager* inputManager) {
	assert(_inputManager == nullptr);
	_inputManager = inputManager;
}

void ServiceLocator::SetApplication(Application* application) {
	assert(_application == nullptr);
	_application = application;
}

void ServiceLocator::SetAudioEngine(AudioEngine* audioEngine) {
	assert(_audioEngine == nullptr);
	_audioEngine = audioEngine;
}

void ServiceLocator::SetSpriteRenderer(SpriteRenderer* spriteRenderer) {
	assert(_spriteRenderer == nullptr);
	_spriteRenderer = spriteRenderer;
}