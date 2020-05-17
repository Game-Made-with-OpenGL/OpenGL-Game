#ifndef SEQUENCEMANAGER_H
#define SEQUENCEMANAGER_H

#include "CharacterBehaviour.h"
#include "Enemy.h"

class SequenceManager {
public:
	SequenceManager();
	~SequenceManager();
	void Init(CharacterBehaviour &player, Enemy &enemy);
	bool gameOver;
	bool turnTake;
	bool inExecuteTurn;
	CharacterBehaviour *player;
	Enemy *enemy;
	void ExecuteSequence();
	void NextTurn();
	int GetTurn();
private:
	int turn = -1;
	float timer;
	float delaySequence;
};

#endif