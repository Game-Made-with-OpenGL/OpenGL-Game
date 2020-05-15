#ifndef CHARACTERINFO_H
#define CHARACTERINFO_H

enum Status { DEFFEND, ATTACK, RUN };

class CharacterInfo {
public :
	CharacterInfo() {

	}

	~CharacterInfo() {

	}

	int hp;
	int attack;
	int deffend;
	Status status;
};

#endif