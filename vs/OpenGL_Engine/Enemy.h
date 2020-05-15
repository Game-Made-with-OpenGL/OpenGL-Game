#ifndef ENEMY_H
#define ENEMY_H

#include "TurnBasedGame.h"

class Enemy {
public :
	void Init();
	void Render();
	void Update();

	void Attack();
	void Deffend();
	void Run();

	void TakeDamage(int damage);

	GameObject enemy;

protected:
	void BuildEnemySprite();
	void DrawEnemySprite();
	void UpdateSpriteAnim();
	float xpos = 0, ypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;
	bool walk_anim = false, onGround = true;
};

#endif