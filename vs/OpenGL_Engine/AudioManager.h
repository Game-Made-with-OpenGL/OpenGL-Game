#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#pragma once


#include <SDL/SDL_mixer.h>
#include <string>
#include <unordered_map>

using namespace std;

class AudioManager {
public:
	AudioManager();
	~AudioManager();
	void Init();
	void PlayBGM();
	void PlaySFX(string name);
private:
	void InputSFX(string name, const char *path);
	Mix_Music* music = NULL;
	int sfx_channel = -1;
	unordered_map<string, Mix_Chunk*> soundEffects;
};

#endif