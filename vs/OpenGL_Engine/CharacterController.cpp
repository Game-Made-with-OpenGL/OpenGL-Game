#include "CharacterController.h"

void CharacterController::Init() {
	CharacterBehaviour::Init();

}

void CharacterController::Update() {
	CharacterBehaviour::Update();

	Controller();
	UpdateSpriteAnim(Time::deltaTime);
}

void CharacterController::Render(){
	CharacterBehaviour::Render();

	DrawPlayerSprite();
	
}

void CharacterController::Controller() {
	ControlPlayerSprite(Time::deltaTime);

	if (Input::GetKeyDown("Attack")) {
		Attack();
	}

	if (Input::GetKeyDown("Deffend")) {
		Deffend();
	}

	if (Input::GetKeyDown("Run")) {
		Run();
	}
}

void CharacterController::ControlPlayerSprite(float deltaTime)
{
	CharacterBehaviour::walk_anim = false;

	if (Input::GetKey("Move Right")) {
		xpos += deltaTime * xVelocity;
		flip = 0;
		walk_anim = true;
	}

	if (Input::GetKey("Move Left")) {
		xpos -= deltaTime * xVelocity;
		flip = 1;
		walk_anim = true;
	}

	if (Input::GetKeyDown("Jump")) {
		if (onGround) {
			yVelocity = -12.0f;
			onGround = false;
		}
	}

	if (Input::GetKeyUp("Jump")) {
		if (yVelocity < -6.0f) {
			yVelocity = -6.0f;
		}
	}

	yVelocity += gravity * deltaTime;
	ypos += deltaTime * yVelocity;

	if (ypos > yposGround) {
		ypos = yposGround;
		yVelocity = 0;
		onGround = true;
	}


	glUniform1i(glGetUniformLocation(player.GetObjectShaderID(), "flip"), flip);

	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos, ypos, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width, frame_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(player.GetObjectShaderID(), "model"), 1, GL_FALSE, value_ptr(model));
}
