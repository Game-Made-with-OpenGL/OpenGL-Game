#include "SequenceManager.h"
#include "Scene.h"

SequenceManager::SequenceManager() {

}

SequenceManager::~SequenceManager() {

}

void SequenceManager::Init(CharacterBehaviour &player, Enemy &enemy) {
	turnTake = false;
	turn = 0;
	inExecuteTurn = true;
	gameOver = false;
	this->player = &player;
	this->enemy = &enemy;
	delaySequence = 2;
	timer = 0;
}

void SequenceManager::NextTurn() {
	turn++;

	if (turn == 2) {
		turn = 0;
	}
}

int SequenceManager::GetTurn() {
	return turn;
}

void SequenceManager::ExecuteSequence() {
	if (gameOver) {
		Scene::UIInstance.ActiveTurnText(CharacterType::NONE);
		return;
	}
	if (inExecuteTurn) {

		timer += (Time::deltaTime / 1000);
		Scene::UIInstance.UpdateTimer(to_string((int) ((delaySequence + 1) - timer)));

		if (turn == 0) {
			Scene::UIInstance.ActiveTurnText(CharacterType::PLAYER);
		}
		else {
			Scene::UIInstance.ActiveTurnText(CharacterType::ENEMY);
		}

		if (timer > delaySequence) {
			Scene::UIInstance.UpdateTimer("");
			timer = 0;
			inExecuteTurn = false;
			if (turn == 1) {			
				enemy->MadeChoice();
			}
			else {			
				player->MadeChoice();
			}
		}
	}

	if (turnTake) {
		timer = 0;
		turnTake = false;
		inExecuteTurn = true;
		NextTurn();
	}
}