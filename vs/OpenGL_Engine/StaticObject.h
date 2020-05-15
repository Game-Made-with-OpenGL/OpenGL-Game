#ifndef STATICOBJECT_H
#define STATICOBJECT

#include "TurnBasedGame.h"

class StaticObject {
public:
	StaticObject();
	~StaticObject();

	void Init();
	void Render();
	void Update();

private:
	GameObject background;
	void CreateBackground();
};

#endif