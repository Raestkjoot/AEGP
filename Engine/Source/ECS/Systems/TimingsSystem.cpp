#include "TimingsSystem.h"

#include "Logger.h"

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

void TimingsSystem::Start() {
	_deltaTimeSamples.resize(_maxSamples);
	// For some reason every other sample from the renderer is bogus.
	// TODO: Fix every other sample being some random high number
	_renderTimeSamples.resize(_maxSamples / 2);
}

void TimingsSystem::Update(float deltaTime) {
	_deltaTimeSamples[_sampleIndex] = deltaTime;
	_sampleIndex = (1 + _sampleIndex) % _maxSamples;

	float avgDeltaTime = 0.0f;
	unsigned long avgRenderTime = 0;

	for (int i = 0; i < _maxSamples; ++i) {
		avgDeltaTime += _deltaTimeSamples[i];
		avgRenderTime += _renderTimeSamples[i / 2];
	}

	avgDeltaTime /= _maxSamples;
	avgRenderTime /= _maxSamples / 2;

	if (_sampleIndex == 0) {
		// Save the average and convert seconds -> milliseconds
		_avgDeltaTime = avgDeltaTime * 1000.0f;
		// render time is in nanoseconds
		_avgRenderTime = static_cast<float>(avgRenderTime); // ns =  / 1000000
		_avgRenderTime /= 1000000.0f;
	}

	ImGui::Begin("Timings");
	ImGui::Text("FPS:    %.0f", 1000.0f / _avgDeltaTime);
	ImGui::Text("Delta:  %f ms", _avgDeltaTime);
	ImGui::Text("Render: %f ms", _avgRenderTime);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}