#ifndef ANIMATION_H
#define ANIMATION_H
#pragma once

#include <string>

using namespace std;

class Animation {
public:
	Animation() {

	}

	~Animation() {

	}

	unsigned int FRAME_DURATION = 1;
	unsigned int NUMBER_OF_FRAME = 1;
	unsigned int offsetIndexY = 0;
	string name;
	bool loop;
};

#endif