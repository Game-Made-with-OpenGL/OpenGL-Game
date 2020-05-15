#ifndef OBJECTRENDER_H
#define OBJECTRENDER_H

#include "CharacterController.h"
#include "StaticObject.h"

class Scene {
public:
	Scene();
	~Scene();
	void Init();
	void Update();
	void Render();

private:
	CharacterController player;
	StaticObject object;
};
#endif