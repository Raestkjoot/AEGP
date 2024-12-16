//#pragma once
//
//#include "Audio.h"
//#include "Utils/Random.h"
//#include "Utils/Logger.h"
//
//#include <glm/glm.hpp>
//
//#include <array>
//#include <string>
//
//template <int ARRAY_LEN>
//class FixedSizeAudioArray {
//private:
//	std::array<Audio, ARRAY_LEN> _audioClips;
//
//	float _volume{ 1.0f };
//	glm::vec2 _pitchRange{ 1.0f, 1.0f };
//	int _lastPlayedIndex = -1;
//	int _numOfElems = 0;
//
//public:
//	void AddAudioFile(const std::string& filename) {
//		if (_numOfElems == ARRAY_LEN) {
//			Logger::PrintWarning("FIXED_SIZE_AUDIO_ARRAY: Failed to add audio file, array is already full.");
//			return;
//		}
//
//		Audio audio;
//		audio.Load(filename);
//		_audioClips[_numOfElems] = std::move(audio);
//		_numOfElems++;
//	}
//
//	void PlayRandom() {
//		int rnd = Random::Range(0, _numOfElems - 1);
//		Play(rnd);
//	}
//
//	void PlayShuffle() {
//		int rnd = Random::Range(0, _numOfElems - 1);
//
//		if (rnd != _lastPlayedIndex) {
//			Play(rnd);
//		}
//		else {
//			rnd = (rnd + 1) % _numOfElems;
//			Play(rnd);
//		}
//
//		_lastPlayedIndex = rnd;
//	}
//
//	void Play(unsigned int index) {
//		if (_numOfElems >= ARRAY_LEN) {
//			Logger::PrintWarning("FIXED_SIZE_AUDIO_ARRAY: Failed to play audio, index out of bounds.");
//			return;
//		}
//
//		float volume = _volume;
//		float pitch = Random::Range(_pitchRange.x, _pitchRange.y);
//
//		_audioClips[index].SetVolume(volume);
//		_audioClips[index].SetPitch(pitch);
//		_audioClips[index].Play();
//	}
//
//	void SetVolume(float volume) {
//		_volume = volume;
//	}
//
//	void SetPitchRange(glm::vec2 pitchRange) {
//		_pitchRange = pitchRange;
//	}
//};