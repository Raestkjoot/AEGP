#include "Audio.h"

#include "AudioEngine.h"
#include "ServiceLocator.h"
#include "Logger.h"

void Audio::Load(const std::string& filename) {
	ServiceLocator::GetAudioEngine()->InitAudioFile(&_audio, filename);
}

void Audio::Play() {
	ma_sound_start(&_audio);
}

void Audio::Pause() {
	ma_sound_stop(&_audio);
}

void Audio::PlayPause() {
	if (ma_sound_is_playing(&_audio)) {
		Pause();
	} else {
		Play();
	}
}

void Audio::Loop(bool shouldLoop) {
	ma_sound_set_looping(&_audio, shouldLoop);
}