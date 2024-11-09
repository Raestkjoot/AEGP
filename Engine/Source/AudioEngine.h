#pragma once

#include <string>

class ma_engine;
class ma_sound;

class AudioEngine {
public:
	AudioEngine();
	~AudioEngine();
	
	void InitAudioFile(ma_sound* audio, const std::string& filename);

private:
	ma_engine* _engine = nullptr;
};