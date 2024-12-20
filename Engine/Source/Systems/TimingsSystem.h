#pragma once

#include "System.h"

#include <vector>

class TimingsSystem : public System {
public:
	// fps (from delta time avg)
	// delta time avg
	// render time avg
	TimingsSystem();
	static TimingsSystem& GetInstance();

	void AddRenderTime(unsigned long renderTime);
	void AddSpritePreperationTime(float prepTime);

protected:
	void Start() override;
	void Update(float deltaTime) override;

private:
	int _maxSamples = 120;
	std::vector<float> _deltaTimeSamples;
	std::vector<unsigned long> _renderTimeSamples;
	std::vector<float> _spritePrepTimeSamples;
	int _sampleIndex = 0;
	float _avgDeltaTime;
	float _avgRenderTime;
	float _avgSpritePrepTime;
};