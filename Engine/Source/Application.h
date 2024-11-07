#pragma once

#include "ECS/Scene.h"

#include <string>

class Window;
class Renderer;
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
	bool IsRunning() const;

	virtual void Initialize();
	void Update(float delta);
	void Cleanup();

protected:
	Scene _curScene{};

	Window* _window = nullptr;
	Renderer* _renderer = nullptr;
	InputManager* _inputManager = nullptr;
	SystemFactory* _systemFactory = nullptr;
	ComponentFactory* _componentFactory = nullptr;

private:
	SceneLoader* _sceneLoader = nullptr;
};