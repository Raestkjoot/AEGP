#pragma once

#include "Application.h"
#include "ECS/Scene.h"

class TestbedApplication : public Application {
public:
	TestbedApplication();

protected:
	void Initialize() override;
	void Update() override;
	void Cleanup() override;

private:
	Scene _mainScene;
	bool _testButtonPressed = false;
	bool _testButtonReleased = false;
};