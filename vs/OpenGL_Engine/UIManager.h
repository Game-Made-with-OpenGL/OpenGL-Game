#ifndef UIMANAGER_H
#define UIMANAGER_H
#pragma once

#include "Text.h"

enum class CharacterType{ PLAYER, ENEMY, NONE};

class UIManager {
public:
	UIManager();
	~UIManager();
	void Init();
	void Update();
	void Render();
	void ActiveVFX(string name, CharacterType type, glm::vec3 color);
	void UpdateTimer(string timer);
	void ActiveTurnText(CharacterType type);
	void UpdateHP(CharacterType type, int value);

	void GameOverRender();
	void SetPlayerWin(string player);
private:
	void AnimatePlayerVFX();
	void AnimateEnemyVFX();
	void ResetStateVFX(CharacterType type);
	Text turnPlayer, turnEnemy;
	Text timer;
	Text vfxEnemy, vfxPlayer;
	Text playerHp, enemyHp;
	Text gameOverText, winPlayer, infoText;
	float animateTime, vfxTimerPlayer, vfxTimerEnemy;
	bool animateVFXEnemy, animateVFXPlayer;

	Text developerMessage, guide, guide1, guide2;

	glm::vec2 originalPosPlayerVFX, originalPosEnemyVFX;

	float opacityPlayerVFX, opacityEnemyVFX, heightPlayerVFX, heightEnemyVFX;
};

#endif
