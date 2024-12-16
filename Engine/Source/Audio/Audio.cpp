#include "Audio.h"

#include "AudioEngine.h"
#include "Utils/ServiceLocator.h"
#include "Utils/Logger.h"

#include <miniaudio.h>


Audio::Audio(Audio&& other) noexcept {
	_audio = other._audio;
	_volume = other._volume;
	_pitch = other._pitch;
	other._audio = nullptr;
}

Audio& Audio::operator=(const Audio& other) noexcept {
	_volume = other._volume;
	_pitch = other._pitch;
	// Currently assuming we will use std::move() on other, 
	// but maybe we want to create a new ma_sound on the engine and copy from other in the future
	_audio = other._audio;

	return *this;
}

Audio::~Audio() {
	ma_sound_uninit(_audio);
	delete _audio;
}

void Audio::Load(const std::string& filename) {
	if (_audio != nullptr) {
		ma_sound_uninit(_audio);
	}
	else {
		_audio = new ma_sound();
	}

	ServiceLocator::GetAudioEngine()->InitAudioFile(_audio, filename);
}

void Audio::Play() {
	if (ma_sound_start(_audio) != MA_SUCCESS) {
		Logger::PrintError("AUDIO: Failed to play audio");
	}
}

void Audio::Pause() {
	if (ma_sound_stop(_audio) != MA_SUCCESS) {
		Logger::PrintError("AUDIO: Failed to pause audio");
	}
}

void Audio::PlayPause() {
	if (ma_sound_is_playing(_audio)) {
		Pause();
	} else {
		Play();
	}
}

void Audio::Loop(bool shouldLoop) {
	ma_sound_set_looping(_audio, shouldLoop);
}

bool Audio::IsPlaying() {
	return ma_sound_is_playing(_audio);
}

void Audio::SetVolume(float volume) {
	ma_sound_set_volume(_audio, volume);
	_volume = volume;
}

float Audio::GetVolume() {
	return _volume;
}

void Audio::SetPitch(float pitch) {
	ma_sound_set_pitch(_audio, pitch);
	_pitch = pitch;
}

float Audio::GetPitch() {
	return _pitch;
}