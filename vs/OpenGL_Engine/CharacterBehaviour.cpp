#include "CharacterBehaviour.h"
#include "Debug.h"
#include "Scene.h"
#include <time.h>  

CharacterBehaviour::CharacterBehaviour() {

}

CharacterBehaviour::~CharacterBehaviour() {

}

void CharacterBehaviour::Init() {
	
	player = GameObject();
	BuildPlayerSprite();
	int hp = 120;
	int attack = 11;
	int deffend = 6;
	info = CharacterInfo(hp, attack, deffend);

	Scene::UIInstance.UpdateHP(CharacterType::PLAYER, info.hp);
	srand(time(NULL));
}

void CharacterBehaviour::Render() {
	
}

void CharacterBehaviour::Update() {
	
}

void CharacterBehaviour::Attack() {
	Scene::AudioInstance.PlaySFX("Attack");
	Scene::UIInstance.ActiveVFX("Attack", CharacterType::PLAYER, glm::vec3(0, 1, 0));
	info.status = Status::ATTACK;

	Scene::sequenceInstance.enemy->TakeDamage(rand() % info.attack + 1);
	Scene::sequenceInstance.turnTake = true;
	inTurn = false;
}

void CharacterBehaviour::Deffend() {
	Scene::UIInstance.ActiveVFX("Defend", CharacterType::PLAYER, glm::vec3(0, 1, 0));
	info.status = Status::DEFFEND;
	Scene::sequenceInstance.turnTake = true;
	inTurn = false;
}

void CharacterBehaviour::Run() {
	Debug::Log("Run");
	info.status = Status::RUN;
	Scene::sequenceInstance.turnTake = true;
	inTurn = false;
}

void CharacterBehaviour::TakeDamage(int damage) {
	Scene::AudioInstance.PlaySFX("Hurt");
	player.spritesheet.SetActiveAnimation("Hurt");
	int takeDamage = 0;

	if (info.status == Status::DEFFEND) {
		takeDamage =  damage - (rand() % info.deffend + 1);
		if (takeDamage < 0) takeDamage = 0;
	}
	else {
		takeDamage = damage;
	}

	info.hp -= takeDamage;

	if (info.hp <= 0) {
		Scene::AudioInstance.PlaySFX("Death");
		info.hp = 0;
		player.spritesheet.SetBaseAnimation("Death");
		player.spritesheet.SetActiveAnimation("Death");
		Scene::sequenceInstance.gameOver = true;
		Scene::UIInstance.SetPlayerWin("Enemy Win");
	}

	Scene::UIInstance.ActiveVFX("-" + to_string(takeDamage) + " HP", CharacterType::PLAYER, glm::vec3(1, 0, 0));
	Scene::UIInstance.UpdateHP(CharacterType::PLAYER, info.hp);
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
	player.spritesheet.SetAnimationState("Death", 60, 6, 1, false);
	player.spritesheet.SetAnimationState("Hurt", 160, 2, 2, false);

	
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
	xpos = 0;
	yposGround = Window::GetScreenHeight() - (player.spritesheet.GetHeight() + 140);
	ypos = yposGround;
	gravity = 0.05f;
	xVelocity = 0.1f;

	player.transform.SetPosition(glm::vec3(xpos, ypos, 0));
}

void CharacterBehaviour::MadeChoice() {
	inTurn = true;
}