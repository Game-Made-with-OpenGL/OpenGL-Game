#ifndef CHARACTERBEHAVIOUR_H
#define CHARACTERBEHAVIOUR_H

#pragma once

#include "TurnBasedGame.h"

class CharacterBehaviour {
public:
	virtual void Init();
	virtual void Render();
	virtual void Update();

	void Attack();
	void Deffend();
	void Run();
	void Mbeek();


	void TakeDamage(int damage);

	GameObject player;

	
protected:
	void BuildPlayerSprite();
	void DrawPlayerSprite();
	void UpdateSpriteAnim();
	float xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	bool walk_anim = false, onGround = true;
};

#endif