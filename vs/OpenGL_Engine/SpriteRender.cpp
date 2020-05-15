#include "SpriteRender.h"
#include "Debug.h"

SpriteRender::SpriteRender() {

}

SpriteRender::SpriteRender(const char* path, float max_number_of_width_frame, float max_number_of_height_frame) {
	// Load and create a texture 
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	unsigned char* image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	frame_width = ((float)width);
	frame_height = ((float)height);
	MAX_NUMBER_OF_FRAME_HEIGHT = max_number_of_height_frame;
	MAX_NUMBER_OF_FRAME_WIDTH = max_number_of_width_frame;
}

SpriteRender::~SpriteRender() {

}

void SpriteRender::SetAnimationState(string nameState, unsigned int frame_dur, unsigned int num_frame, unsigned int offsetY, bool loopable) {
	Animation anim;
	anim.FRAME_DURATION = frame_dur;
	anim.offsetIndexY = offsetY;
	anim.name = nameState;
	anim.loop = loopable;
	anim.NUMBER_OF_FRAME = num_frame;
	animations.insert(pair<string, Animation>(nameState, anim));
}

void SpriteRender::Animate(string nameState) {

	if (nameState != lastState) {
		SetActiveAnimation(nameState);
		lastState = nameState;
		frame_dur = 0;
		frame_idx = 0;
		frame_idy = activeAnimation.offsetIndexY;
	}
	// Update animation
	frame_dur += Time::deltaTime;

	if (frame_dur > activeAnimation.FRAME_DURATION) {
		frame_dur = 0;
		if (frame_idx == activeAnimation.NUMBER_OF_FRAME - 1) {
			if (activeAnimation.loop) frame_idx = 0;
			else SetActiveAnimation(baseAnimation.name);
		}
		else {
			frame_idx++;
		}
	}
}

float SpriteRender::GetWidth() {
	return (frame_width / MAX_NUMBER_OF_FRAME_WIDTH);
}

float SpriteRender::GetHeight() {
	return frame_height/ MAX_NUMBER_OF_FRAME_HEIGHT;
}

Animation SpriteRender::GetActiveAnimation() {
	return activeAnimation;
}

GLuint SpriteRender::GetTextureID() {
	return textureId;
}

void SpriteRender::SetActiveAnimation(string animationName) {
	auto it = animations.find(animationName);
	if (it != animations.end()) {
		// Found the key
		activeAnimation = it->second;
		frame_dur = 0;
		frame_idx = 0;
		frame_idy = activeAnimation.offsetIndexY;
	}
	else {
		Debug::Log("FATAL ERROR");
	}
}

void SpriteRender::SetBaseAnimation(string nameState) {
	auto it = animations.find(nameState);
	if (it != animations.end()) {
		baseAnimation = it->second;
	}
	else {
		Debug::Log("FATAL ERROR:: CAN'T FIND BASE ANIMATION");
	}
}