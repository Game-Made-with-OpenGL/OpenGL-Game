#ifndef OBJECTRENDER_H
#define OBJECTRENDER_H

#include "CharacterController.h"
#include "StaticObject.h"
#include "SequenceManager.h"
#include "Enemy.h"
#include "UIManager.h"
#include "AudioManager.h"

class Scene {
public:
	Scene();
	~Scene();
	void Init();
	void Update();
	void Render();

	static SequenceManager sequenceInstance;
	static UIManager UIInstance;
	static AudioManager AudioInstance;
private:
	CharacterController player;
	StaticObject object;
	Enemy enemy;
};
#endif