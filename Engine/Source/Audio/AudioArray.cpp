#include "AudioArray.h"

#include "Audio.h"
#include "Utils/Random.h"
#include "Utils/Logger.h"

void AudioArray::AddAudioFile(const std::string& fileName) {
	_audioClips.emplace_back();
	_audioClips.back().Load(fileName);
}

void AudioArray::PlayRandom() {
	int rnd = Random::Range(0, _audioClips.size() - 1);
	Play(rnd);
}

void AudioArray::PlayShuffle() {
	int rnd = Random::Range(0, _audioClips.size() - 1);

	if (rnd != _lastPlayedIndex) {
		Play(rnd);
	} else {
		rnd = (rnd + 1) % _audioClips.size();
		Play(rnd);
	}

	_lastPlayedIndex = rnd;
}

void AudioArray::Play(int index) {
	float volume = _volume;
	float pitch = Random::Range(_pitchRange.x, _pitchRange.y);

	_audioClips[index].SetVolume(volume);
	_audioClips[index].SetPitch(pitch);
	_audioClips[index].Play();
}

void AudioArray::SetVolume(float volume) {
	_volume = volume;
}

void AudioArray::SetPitchRange(glm::vec2 pitchRange) {
	_pitchRange = pitchRange;
}