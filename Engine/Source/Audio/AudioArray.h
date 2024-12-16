#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>

class Audio;

class AudioArray {
public:
	void AddAudioFile(const std::string& fileName);

	void PlayRandom();
	void PlayShuffle();
	void Play(int index);
	void SetVolume(float volume);
	void SetPitchRange(glm::vec2 pitchRange);

private:
	std::vector<Audio> _audioClips;

	float _volume{ 1.0f };
	glm::vec2 _pitchRange{1.0f, 1.0f};
	int _lastPlayedIndex = -1;
};