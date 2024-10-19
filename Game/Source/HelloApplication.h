#pragma once

#include "Application.h"
#include "ECS/Scene.h"

class HelloApplication : public Application {
public:
	HelloApplication();

protected:
	void Initialize() override;

private:
	bool _testButtonPressed = false;
	bool _testButtonReleased = false;
};