#include "TimingsSystem.h"

#include "Utils/Logger.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>

#include <assert.h>

static TimingsSystem* _instance = nullptr;

TimingsSystem::TimingsSystem() {
	assert(!_instance);
	_instance = this;
}

TimingsSystem& TimingsSystem::GetInstance() {
	assert(_instance);
	return *_instance;
}

void TimingsSystem::AddRenderTime(unsigned long renderTime) {
	_renderTimeSamples[_sampleIndex / 2] = renderTime;
}

void TimingsSystem::AddSpritePreperationTime(float prepTime) {
	_spritePrepTimeSamples[_sampleIndex] = prepTime;
}

void TimingsSystem::Start() {
	_deltaTimeSamples.resize(_maxSamples);
	// For some reason every other sample from the renderer is bogus.
	// TODO: Fix every other sample being some random high number
	_renderTimeSamples.resize(_maxSamples / 2);
	_spritePrepTimeSamples.resize(_maxSamples);
}

void TimingsSystem::Update(float deltaTime) {
	_deltaTimeSamples[_sampleIndex] = deltaTime;
	_sampleIndex = (1 + _sampleIndex) % _maxSamples;

	float avgDeltaTime = 0.0f;
	unsigned long avgRenderTime = 0;
	float avgSpritePrepTime = 0.0f;

	for (int i = 0; i < _maxSamples; ++i) {
		avgDeltaTime += _deltaTimeSamples[i];
		avgRenderTime += _renderTimeSamples[i / 2];
		avgSpritePrepTime += _spritePrepTimeSamples[i];
	}

	avgDeltaTime /= _maxSamples;
	avgRenderTime /= _maxSamples / 2;
	avgSpritePrepTime /= _maxSamples;

	if (_sampleIndex == 0) {
		// Save the average delta time and convert seconds -> milliseconds
		_avgDeltaTime = avgDeltaTime * 1000.0f;
		// render time is in nanoseconds
		_avgRenderTime = static_cast<float>(avgRenderTime); // ns =  / 1000000
		_avgRenderTime /= 1000000.0f;
		// Save the average sprite prep time and convert seconds -> milliseconds
		_avgSpritePrepTime = avgSpritePrepTime * 1000.0f;
	}

	ImGui::Begin("Timings");
	ImGui::Text("FPS:    %.0f", 1000.0f / _avgDeltaTime);
	ImGui::Text("Delta:  %f ms", _avgDeltaTime);
	ImGui::Text("Render: %f ms", _avgRenderTime);
	ImGui::Text("Sprite Prep: %f ms", _avgSpritePrepTime);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}