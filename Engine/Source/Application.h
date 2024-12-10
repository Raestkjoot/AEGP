#pragma once

#include "Scene/Scene.h"

#include <string>

class Window;
class Renderer;
class AudioEngine;
class InputManager;
class SceneLoader;
class SystemFactory;
class ComponentFactory;

class Application {
public:
	Application(int width, int height, const char* title);

	void Run();
	void LoadScene(const std::string& sceneName);
	void Quit();

protected:
	virtual void Initialize();

	SystemFactory* _systemFactory = nullptr;
	ComponentFactory* _componentFactory = nullptr;

private:
	bool IsRunning() const;
	void Cleanup();

	Scene* _curScene = nullptr;
	Window* _window = nullptr;
	Renderer* _renderer = nullptr;
	AudioEngine* _audioEngine = nullptr;
	InputManager* _inputManager = nullptr;
	SceneLoader* _sceneLoader = nullptr;
};