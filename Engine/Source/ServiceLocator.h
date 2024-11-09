#pragma once

#include "cassert"

class InputManager;
class Application;
class AudioEngine;
class SpriteRenderer;

class ServiceLocator {
public:
	static InputManager* GetInputManager() {
		assert(_inputManager != nullptr);
		return _inputManager;
	}
	static void SetInputManager(InputManager* inputManager);

	static Application* GetApplication() {
		assert(_application != nullptr);
		return _application;
	}
	static void SetApplication(Application* application);

	static AudioEngine* GetAudioEngine() {
		assert(_audioEngine != nullptr);
		return _audioEngine;
	}
	static void SetAudioEngine(AudioEngine* audioEngine);

	static SpriteRenderer* GetSpriteRenderer() {
		assert(_spriteRenderer != nullptr);
		return _spriteRenderer;
	}
	static void SetSpriteRenderer(SpriteRenderer* spriteRenderer);

private:
	static InputManager* _inputManager;
	static Application* _application;
	static AudioEngine* _audioEngine;
	static SpriteRenderer* _spriteRenderer;
};