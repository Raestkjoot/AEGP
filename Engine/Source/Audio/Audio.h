#pragma once

#include <string>

class ma_sound;

class Audio {
public:
	Audio() = default;
	Audio(Audio&& other) noexcept;
	~Audio();

	void Load(const std::string& filename);
	void Play();
	void Pause();
	void PlayPause();
	void Loop(bool shouldLoop);
	bool IsPlaying();

	void SetVolume(float volume);
	float GetVolume();
	void SetPitch(float pitch);
	float GetPitch();

private:
	ma_sound* _audio = nullptr;

	float _volume = 1.0f;
	float _pitch = 1.0f;
};