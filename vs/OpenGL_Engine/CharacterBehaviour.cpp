#include "CharacterBehaviour.h"
#include "Debug.h"

void CharacterBehaviour::Init() {
	
	player = GameObject();
	BuildPlayerSprite();
}

void CharacterBehaviour::Render() {
	
}

void CharacterBehaviour::Update() {
	
}

void CharacterBehaviour::Attack() {
	Debug::Log("Attack");
}

void CharacterBehaviour::Deffend() {
	Debug::Log("Deffend");
}

void CharacterBehaviour::Run() {
	Debug::Log("Run");
}

void CharacterBehaviour::TakeDamage(int damage) {
	Debug::Log(string("Ouch Take ") + to_string(damage) + string(" hit"));
}

void CharacterBehaviour::UpdateSpriteAnim()
{
	player.Animate(player.spritesheet.GetActiveAnimation().name);
}

void CharacterBehaviour::DrawPlayerSprite() {
	player.Render();
}

void CharacterBehaviour::BuildPlayerSprite()
{
	player.BuildShader("spriteAnim.vert", "spriteAnim.frag", nullptr);

	player.ApplyTexture("spritesheet/playerspritesheet.png",6, 4);
	player.spritesheet.SetAnimationState("Idle", 140, 3, 3);
	player.spritesheet.SetActiveAnimation("Idle");
	player.spritesheet.SetBaseAnimation("Idle");

	player.spritesheet.SetAnimationState("Attack", 80, 4, 0, false);

	
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	player.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(Window::GetScreenWidth()), static_cast<GLfloat>(Window::GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	player.shader.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(player.GetObjectShaderID(), "projection"), 1, GL_FALSE, value_ptr(projection));

	player.transform.Scale(vec3(player.spritesheet.GetWidth() * 1.8f, player.spritesheet.GetHeight() * 1.8f, 1));

	// set sprite position, gravity, velocity
	//xpos = (Window::GetScreenWidth() - player.spritesheet.GetWidth());
	xpos = -30;
	yposGround = Window::GetScreenHeight() - (player.spritesheet.GetHeight() + 140);
	ypos = yposGround;
	gravity = 0.05f;
	xVelocity = 0.1f;
}