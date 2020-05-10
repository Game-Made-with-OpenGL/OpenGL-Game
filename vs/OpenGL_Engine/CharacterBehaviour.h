#ifndef CHARACTERBEHAVIOUR_H
#define CHARACTERBEHAVIOUR_H

#pragma once

#define NUM_FRAMES 8
#define FRAME_DUR 80

#include "TurnBasedGame.h"

class CharacterBehaviour {
public:
	virtual void Init();
	virtual void Render();
	virtual void Update();

	void Attack();
	void Deffend();
	void Run();

	void TakeDamage(int damage);

	GameObject player;

	
protected:
	void BuildPlayerSprite();
	void DrawPlayerSprite();
	void UpdateSpriteAnim(float deltaTime);
	float frame_dur = 0, xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	GLuint texture;
	bool walk_anim = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0;
	float frame_width = 0, frame_height = 0;
};

#endif