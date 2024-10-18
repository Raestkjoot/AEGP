#pragma once

class Window;
class Renderer;
class InputManager;

class Application {
public:
	Application(int width, int height, const char* title);

	void Run();

protected:
	bool IsRunning() const;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Cleanup();

protected:
	Window* _window = nullptr;
	Renderer* _renderer = nullptr;
	InputManager* _inputManager = nullptr;
};