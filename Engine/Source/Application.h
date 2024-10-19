#pragma once

class Scene;
class Window;
class Renderer;
class InputManager;

class Application {
public:
	Application(int width, int height, const char* title);

	void Run();
	void Quit();

protected:
	bool IsRunning() const;

	virtual void Initialize();
	void Update(float delta);
	void Cleanup();

protected:
	Scene* _curScene = nullptr;
	Window* _window = nullptr;
	Renderer* _renderer = nullptr;
	InputManager* _inputManager = nullptr;
};