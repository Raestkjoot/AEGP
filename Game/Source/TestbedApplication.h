#pragma once

#include "Application.h"

class TestbedApplication : public Application {
public:
	TestbedApplication();

protected:
	void Initialize() override;
	void Update() override;
	void Render() override;
	void Cleanup() override;
};