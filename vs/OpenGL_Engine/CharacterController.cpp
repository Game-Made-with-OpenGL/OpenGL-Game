#include "CharacterController.h"

CharacterController::CharacterController() {

}

CharacterController::~CharacterController(){
}

void CharacterController::Init() {
	CharacterBehaviour::Init();

}

void CharacterController::Update() {
	CharacterBehaviour::Update();
	Controller();
	UpdateSpriteAnim();
}

void CharacterController::Render(){
	CharacterBehaviour::Render();

	DrawPlayerSprite();
	
}

void CharacterController::Controller() {
	if (inTurn) {
		ControlPlayerSprite(Time::deltaTime);

		if (Input::GetKeyDown("Attack")) {
			Attack();
			player.spritesheet.SetActiveAnimation("Attack");
		} else if (Input::GetKeyDown("Deffend")) {
			Deffend();
		}
	}
}

void CharacterController::ControlPlayerSprite(float deltaTime)
{
	CharacterBehaviour::walk_anim = false;

	if (ypos > yposGround) {
		ypos = yposGround;
		yVelocity = 0;
		onGround = true;
	}


	glUniform1i(glGetUniformLocation(player.GetObjectShaderID(), "flip"), 0);

	player.transform.SetPosition(vec3(xpos, ypos, 0.0f));
}
