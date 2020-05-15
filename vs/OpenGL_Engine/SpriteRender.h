#ifndef SPRITERENDER_H
#define SPRITERENDER
#pragma once

#include <GL/glew.h>
#include <unordered_map>
#include <SOIL/SOIL.h>
#include "Time.h"
#include "Animation.h"

using namespace std;

class SpriteRender {
public:
	SpriteRender(const char* path, float max_number_of_width_frame = 1, float max_number_of_height_frame = 1);
	SpriteRender();
	~SpriteRender();
	unsigned int flipX = 0, flipY = 0;
	void SetAnimationState(string nameState, unsigned int frame_dur, unsigned int num_frame, unsigned int offsetY, bool loopable = true);
	void SetBaseAnimation(string nameState);
	void Animate(string nameState);
	float GetWidth();
	float GetHeight();
	unsigned int frame_idx = 0, frame_idy = 0;
	GLuint GetTextureID();
	Animation GetActiveAnimation();
	void SetActiveAnimation(string animationName);
	float MAX_NUMBER_OF_FRAME_HEIGHT, MAX_NUMBER_OF_FRAME_WIDTH;
private:
	GLuint textureId;	
	float frame_width = 0, frame_height = 0;
	int  height, width;
	float frame_dur;
	
	unordered_map<string, Animation> animations;
	Animation activeAnimation;
	Animation baseAnimation;
	string lastState;
};
#endif
