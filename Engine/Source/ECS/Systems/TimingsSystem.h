#pragma once

#include "ECS/System.h"

#include <vector>

#define SAMPLE_COUNT 20

class TimingsSystem : public System {
public:
	// fps (from delta time avg)
	// delta time avg
	// render time avg
	TimingsSystem();
	static TimingsSystem& GetInstance();

	void AddRenderTime(unsigned long renderTime);

protected:
	void Start() override;
	void Update(float deltaTime) override;

private:
	int _maxSamples = 120;
	std::vector<float> _deltaTimeSamples;
	std::vector<unsigned long> _renderTimeSamples;
	int _sampleIndex = 0;
	float _avgDeltaTime;
	float _avgRenderTime;
};