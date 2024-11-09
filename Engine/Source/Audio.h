#pragma once

#include <miniaudio.h>

#include <string>

class Audio {
public:
	void Load(const std::string& filename);
	void Play();
	void Pause();
	void PlayPause();
	void Loop(bool shouldLoop);

private:
	ma_sound _audio;
};