#include "AudioManager.h"
#include "Debug.h"

AudioManager::AudioManager() {

}

AudioManager::~AudioManager() {

}

void AudioManager::Init() {
	int flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG;
	if (flags != Mix_Init(flags)) {
		Debug::Log("Unable to initialize mixer: " + string(Mix_GetError()));
	}

	int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		Debug::Log("Unable to initialize audio: " + string(Mix_GetError()));
	}


	music = Mix_LoadMUS("audio/01TownBGM-guitar.wav");
	if (music == NULL) {
		Debug::Log("Unable to load Music file: " + string(Mix_GetError()));
	}

	InputSFX("Hurt", "audio/grunting_1_ian.wav");
	InputSFX("Attack", "audio/attack.wav");
	InputSFX("Death", "audio/death_1_sean.wav");
}

void AudioManager::InputSFX(string name, const char* path) {
	Mix_Chunk* sound = Mix_LoadWAV(path);

	if (sound == NULL) {
		Debug::Log("Unable to load WAV file: " + string(Mix_GetError()));
	}
	else {
		soundEffects.insert(pair<string, Mix_Chunk*>(name, sound));
	}
}

void AudioManager::PlayBGM() {

	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, -1);
		SDL_Delay(150);
	}
}

void AudioManager::PlaySFX(string name) {
	auto it = soundEffects.find(name);
	if (it != soundEffects.end()) {
		// Found the key
		sfx_channel = Mix_PlayChannel(-1, it->second, 0);
		if (sfx_channel == -1) {
			Debug::Log("Unable to play WAV file: " + string(Mix_GetError()));
		}
	}
	else {
		// Didn't find the key
		Debug::Log("Doesn't find audio");
	}
	
}