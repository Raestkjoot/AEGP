#pragma once

class Application {
public:
	Application(int width, int height, const char* title);

	void Run();

protected:
	bool IsRunning() const;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;

private:
	bool _isRunning = true;
};