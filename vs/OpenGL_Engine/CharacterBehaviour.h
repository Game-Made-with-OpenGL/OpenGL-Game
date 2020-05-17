#ifndef CHARACTERBEHAVIOUR_H
#define CHARACTERBEHAVIOUR_H

#pragma once

#include "TurnBasedGame.h"
#include "CharacterInfo.h"

class CharacterBehaviour {
public:
	CharacterBehaviour();
	~CharacterBehaviour();

	virtual void Init();
	virtual void Render();
	virtual void Update();

	void Attack();
	void Deffend();
	void Run();
	void MadeChoice();


	void TakeDamage(int damage);

	GameObject player;
	CharacterInfo info;
	
protected:
	void BuildPlayerSprite();
	void DrawPlayerSprite();
	void UpdateSpriteAnim();
	float xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	bool walk_anim = false, onGround = true, inTurn = false;
};

#endif