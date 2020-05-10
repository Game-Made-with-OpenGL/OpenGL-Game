#ifndef TURNBASEDGAME_H
#define TURNBASEDGAME_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "ScratchEngine.h"
#include "Shader.h"
#include "GameObject.h"


using namespace glm;

class TurnBasedGame :
	public Engine::ScratchEngine
{
public:
	TurnBasedGame();
	~TurnBasedGame();
	virtual void Init();
	virtual void Update();
	virtual void Render();
	
private:	
	void InputMapping();

};
#endif

