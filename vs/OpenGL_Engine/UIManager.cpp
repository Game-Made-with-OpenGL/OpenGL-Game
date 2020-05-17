#include "UIManager.h"

UIManager::UIManager() {
	vfxPlayer = Text();
	vfxEnemy = Text();
	turnPlayer = Text();
	turnEnemy = Text();
	timer = Text();
	playerHp = Text();
	enemyHp = Text();

	developerMessage = Text();
	guide = Text();
	guide1 = Text();
	guide2 = Text();
}

UIManager::~UIManager() {

}

void UIManager::Init() {
	animateTime = 1;
	glm::vec4 color;
	playerHp.Init();
	playerHp.SetSize(0.5f);
	playerHp.SetPosition(glm::vec2(165, 460));

	enemyHp.Init();
	enemyHp.SetSize(0.5f);
	enemyHp.SetPosition(glm::vec2(1085, 530));

	turnPlayer.Init();
	turnPlayer.SetText("Player Turn");
	turnPlayer.SetSize(0.5f);
	turnPlayer.SetPosition(glm::vec2(135, 430));
	color = glm::vec4(0, 1, 1, 0.0f);
	turnPlayer.SetColor(color);

	turnEnemy.Init();
	turnEnemy.SetText("Enemy Turn");
	turnEnemy.SetSize(0.5f);
	turnEnemy.SetPosition(glm::vec2(1055, 490));
	color = glm::vec4(0, 1, 1, 0.0f);
	turnEnemy.SetColor(color);

	vfxPlayer.Init();
	vfxPlayer.SetSize(0.4f);
	originalPosPlayerVFX = glm::vec2(250, 500);
	vfxPlayer.SetPosition(originalPosPlayerVFX);
	color = glm::vec4(vfxPlayer.GetColor().r, vfxPlayer.GetColor().g, vfxPlayer.GetColor().b, 0.0f);
	vfxPlayer.SetColor(color);

	vfxEnemy.Init();
	vfxEnemy.SetSize(0.4f);
	originalPosEnemyVFX = glm::vec2(990, 560);
	vfxEnemy.SetPosition(originalPosEnemyVFX);
	color = glm::vec4(vfxEnemy.GetColor().r, vfxEnemy.GetColor().g, vfxEnemy.GetColor().b, 0.0f);
	vfxEnemy.SetColor(color);

	timer.Init();
	timer.SetPosition(glm::vec2(600, 150));
	timer.SetSize(1.3f);

	gameOverText.Init();
	gameOverText.SetPosition(glm::vec2(470, 200));
	gameOverText.SetText("GAME OVER");
	gameOverText.SetColor(glm::vec4(1,0,0,1));
	gameOverText.SetSize(1.4f);

	winPlayer.Init();
	winPlayer.SetPosition(glm::vec2(540, 300));
	winPlayer.SetColor(glm::vec4(0, 1, 0, 1));
	winPlayer.SetSize(1.0f);

	infoText.Init();
	infoText.SetText("Press Esc to Quit");
	infoText.SetPosition(glm::vec2(500, 500));
	infoText.SetSize(0.8f);

	developerMessage.Init();
	developerMessage.SetText("This is just a prototype to test our game engine is full Works or not based on OpenGL. This game engine is developed by TW from Faculty of Computer Science, University of Brawijaya");
	developerMessage.SetSize(0.4f);
	developerMessage.SetPosition(glm::vec2(10, 20));

	guide.Init();
	guide.SetText("HOW TO PLAY : ");
	guide.SetSize(0.7f);
	guide.SetPosition(glm::vec2(10, 60));

	guide1.Init();
	guide1.SetText("Press 1 to Attack when in ur Turn.");
	guide1.SetSize(0.4f);
	guide1.SetPosition(glm::vec2(10, 85));

	guide2.Init();
	guide2.SetText("Press 2 to Defend yourself against enemies attack in the next turn");
	guide2.SetSize(0.4f);
	guide2.SetPosition(glm::vec2(10, 100));
}

void UIManager::Update() {
	if (animateVFXPlayer) {
		AnimatePlayerVFX();
	}
	
	if (animateVFXEnemy) {
		AnimateEnemyVFX();	
	}

}

void UIManager::Render() {
	vfxPlayer.Render();
	vfxEnemy.Render();
	turnPlayer.Render();
	turnEnemy.Render();
	timer.Render();
	playerHp.Render();
	enemyHp.Render();

	developerMessage.Render();
	guide.Render();
	guide1.Render();
	guide2.Render();
}

void UIManager::ActiveVFX(string name, CharacterType type, glm::vec3 color) {
	ResetStateVFX(type);
	if (type == CharacterType::PLAYER) {
		vfxPlayer.SetText(name);
		vfxPlayer.SetColor(glm::vec4(color, opacityPlayerVFX));
		animateVFXPlayer = true;
	}
	else {
		vfxEnemy.SetText(name);	
		vfxEnemy.SetColor(glm::vec4(color, opacityEnemyVFX));
		animateVFXEnemy = true;
	}
}

void UIManager::ActiveTurnText(CharacterType type) {
	if (type == CharacterType::PLAYER) {
		glm::vec4 color = glm::vec4(turnPlayer.GetColor().r, turnPlayer.GetColor().g, turnPlayer.GetColor().b, 1.0f);
		turnPlayer.SetColor(color);

		color = glm::vec4(turnEnemy.GetColor().r, turnEnemy.GetColor().g, turnEnemy.GetColor().b, 0.0f);
		turnEnemy.SetColor(color);
	}
	else if (type == CharacterType::ENEMY) {
		glm::vec4 color = glm::vec4(turnPlayer.GetColor().r, turnPlayer.GetColor().g, turnPlayer.GetColor().b, 0.0f);
		turnPlayer.SetColor(color);

		color = glm::vec4(turnEnemy.GetColor().r, turnEnemy.GetColor().g, turnEnemy.GetColor().b, 1.0f);
		turnEnemy.SetColor(color);
	}
	else {
		glm::vec4 color = glm::vec4(turnPlayer.GetColor().r, turnPlayer.GetColor().g, turnPlayer.GetColor().b, 0.0f);
		turnPlayer.SetColor(color);
		turnEnemy.SetColor(color);
	}
}

void UIManager::AnimatePlayerVFX() {
	vfxTimerPlayer += (Time::deltaTime / 1000);

	if (vfxTimerPlayer > animateTime) {
		vfxTimerPlayer = 0;
		animateVFXPlayer = false;
		vfxPlayer.SetPosition(originalPosPlayerVFX);
		vfxPlayer.SetColor(glm::vec4(vfxPlayer.GetColor().r, vfxPlayer.GetColor().g, vfxPlayer.GetColor().b, 0.0f));
		vfxPlayer.SetText("");
	}

	opacityPlayerVFX = 1.0f - (vfxTimerPlayer / animateTime);
	heightPlayerVFX = (vfxTimerPlayer / animateTime) * 2.0f;
	vfxPlayer.SetPosition(glm::vec2(vfxPlayer.GetPosition().x, vfxPlayer.GetPosition().y - heightPlayerVFX));
	vfxPlayer.SetColor(glm::vec4(vfxPlayer.GetColor().r, vfxPlayer.GetColor().g, vfxPlayer.GetColor().b, opacityPlayerVFX));
}

void UIManager::AnimateEnemyVFX() {
	vfxTimerEnemy += (Time::deltaTime / 1000);

	if (vfxTimerEnemy > animateTime) {
		vfxTimerEnemy = 0;
		animateVFXEnemy = false;
		vfxEnemy.SetPosition(originalPosEnemyVFX);
		vfxEnemy.SetColor(glm::vec4(vfxEnemy.GetColor().r, vfxEnemy.GetColor().g, vfxEnemy.GetColor().b, 0.0f));
		vfxEnemy.SetText("");
	}

	opacityEnemyVFX = 1.0f - (vfxTimerEnemy / animateTime);
	heightEnemyVFX = (vfxTimerEnemy / animateTime) * 2.0f;
	vfxEnemy.SetPosition(glm::vec2(vfxEnemy.GetPosition().x, vfxEnemy.GetPosition().y - heightEnemyVFX));
	vfxEnemy.SetColor(glm::vec4(vfxEnemy.GetColor().r, vfxEnemy.GetColor().g, vfxEnemy.GetColor().b, opacityEnemyVFX));
}

void UIManager::UpdateHP(CharacterType type, int value) {
		if (type == CharacterType::PLAYER) {
			playerHp.SetText(to_string(value));
		}
		else {
			enemyHp.SetText(to_string(value));
		}
}

void UIManager::UpdateTimer(string timer) {
	this->timer.SetText(timer);
}

void UIManager::ResetStateVFX(CharacterType type) {
	if (type == CharacterType::PLAYER) {
		animateVFXPlayer = false;
		vfxTimerPlayer = 0;
		opacityPlayerVFX = 1;
		vfxPlayer.SetPosition(originalPosPlayerVFX);
		vfxPlayer.SetColor(glm::vec4(vfxPlayer.GetColor().r, vfxPlayer.GetColor().g, vfxPlayer.GetColor().b, opacityPlayerVFX));
	}
	else {
		animateVFXEnemy = false;
		vfxTimerEnemy = 0;
		opacityEnemyVFX = 1;
		vfxEnemy.SetPosition(originalPosEnemyVFX);
		vfxEnemy.SetColor(glm::vec4(vfxEnemy.GetColor().r, vfxEnemy.GetColor().g, vfxEnemy.GetColor().b, opacityEnemyVFX));
	}
}

void UIManager::GameOverRender() {
	
	gameOverText.Render();
	winPlayer.Render();
	infoText.Render();
}

void UIManager::SetPlayerWin(string player) {
	winPlayer.SetText(player);
}