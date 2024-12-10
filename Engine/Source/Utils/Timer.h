#pragma once

#include <chrono>

class Timer {
public:
	Timer();

	float Tick();

private:
	std::chrono::time_point<std::chrono::steady_clock> _lastTick;
};