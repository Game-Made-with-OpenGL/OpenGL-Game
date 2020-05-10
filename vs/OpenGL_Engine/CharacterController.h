#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "CharacterBehaviour.h"
#include "Input.h"

class CharacterController : public CharacterBehaviour {
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	void ControlPlayerSprite(float deltaTime);
	void Controller();
};

#endif