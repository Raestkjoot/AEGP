#include "AudioArray.h"

#include "Audio.h"

#include <cstdlib>

void AudioArray::AddAudioFile(const std::string& fileName) {
	_audioClips.emplace_back();
	_audioClips.back().Load(fileName);
}

void AudioArray::PlayRandom() {
	int rnd = std::rand() % _audioClips.size();
	Play(rnd);
}

void AudioArray::PlayShuffle() {
	int rnd = std::rand() % _audioClips.size();

	if (rnd != _lastPlayedIndex) {
		Play(rnd);
	} else {
		rnd = (rnd + 1) % _audioClips.size();
		Play(rnd);
	}

	_lastPlayedIndex = rnd;
}

void AudioArray::Play(int index) {
	float volume = _volumeRange.x + (static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / _volumeRange.y)));
	float pitch = _pitchRange.x + (static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / _pitchRange.y)));

	_audioClips[index].SetVolume(volume);
	_audioClips[index].SetPitch(pitch);
	_audioClips[index].Play();
}

void AudioArray::SetVolumeRange(glm::vec2 volumeRange) {
	_volumeRange = volumeRange;
}

void AudioArray::SetPitchRange(glm::vec2 pitchRange) {
	_pitchRange = pitchRange;
}