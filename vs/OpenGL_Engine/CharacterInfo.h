#ifndef CHARACTERINFO_H
#define CHARACTERINFO_H

enum class Status { DEFFEND, ATTACK, RUN , IDLE};

class CharacterInfo {
public :
	CharacterInfo() {

	}

	CharacterInfo(int hp, int attack, int defend) {
		this->hp = hp;
		this->maxHP = hp;
		this->attack = attack;
		this->deffend = defend;
		this->status = Status::IDLE;
	}

	~CharacterInfo() {

	}

	int maxHP;
	int hp;
	int attack;
	int deffend;
	Status status;
};

#endif