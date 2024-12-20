#pragma once

#include "Application.h"
#include "Scene/Scene.h"

class PrototypeApplication : public Application {
public:
	PrototypeApplication();

protected:
	void Initialize() override;

private:
	bool _testButtonPressed = false;
	bool _testButtonReleased = false;
};