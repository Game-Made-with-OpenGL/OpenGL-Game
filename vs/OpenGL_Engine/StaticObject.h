#ifndef STATICOBJECT_H
#define STATICOBJECT

#include "TurnBasedGame.h"

class StaticObject {
public:
	StaticObject();
	~StaticObject();

	void Init();
	void Render();
	void LateRender();
	void Update();

	GameObject transparentPanel;
private:
	GameObject background;
	
	void CreateBackground();
	void CreateTransparent();
};

#endif