#pragma once

#include "Application.h"
#include "ECS/Scene.h"

class TestbedApplication : public Application {
public:
	TestbedApplication();

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;

private:
	Scene _mainScene;
};