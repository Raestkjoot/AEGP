#include "AudioEngine.h"

#include "Utils/Logger.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

AudioEngine::AudioEngine() : _engine(new ma_engine()) {
	if (ma_engine_init(NULL, _engine) != MA_SUCCESS) {
		Logger::PrintError("AUDIO_ENGINE: Failed to initialize miniaudio engine");
	}
}

AudioEngine::~AudioEngine() {
	ma_engine_uninit(_engine);
	delete _engine;
}

void AudioEngine::InitAudioFile(ma_sound* audio, const std::string& filename) {
	if (ma_sound_init_from_file(_engine, filename.c_str(), MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, NULL, audio) != MA_SUCCESS) {
		Logger::PrintError("AUDIO_ENGINE: Failed to initialize audio from file '{}'.", filename);
	}
}