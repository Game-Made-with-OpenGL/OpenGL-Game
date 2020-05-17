#include "Enemy.h"
#include "Scene.h"
#include "Debug.h"
#include <time.h>  

void Enemy::Init() {
	enemy = GameObject();
	BuildEnemySprite();
	int hp = 120;
	int attack = 11;
	int deffend = 6;
	info = CharacterInfo(hp, attack, deffend);

	Scene::UIInstance.UpdateHP(CharacterType::ENEMY, info.hp);
	srand(time(NULL));
}

void Enemy::Render() {
	DrawEnemySprite();
}

void Enemy::Update() {
	UpdateSpriteAnim();
}

void Enemy::Attack() {
	Scene::AudioInstance.PlaySFX("Attack");
	Scene::UIInstance.ActiveVFX("Attack", CharacterType::ENEMY, glm::vec3(0, 1, 0));
	info.status = Status::ATTACK;

	enemy.spritesheet.SetActiveAnimation("Attack");

	Scene::sequenceInstance.player->TakeDamage(rand() % info.attack + 1);
	Scene::sequenceInstance.turnTake = true;
}

void Enemy::Deffend() {
	Scene::UIInstance.ActiveVFX("Defend", CharacterType::ENEMY, glm::vec3(0, 1, 0));
	info.status = Status::DEFFEND;

	Scene::sequenceInstance.turnTake = true;
}

void Enemy::Run() {
	Scene::sequenceInstance.turnTake = true;
}

void Enemy::MadeChoice() {
	int choice = rand() % 2;

	if (choice == 0) {
		Attack();
	}
	else if (choice == 1) {
		Deffend();
	}
}

void Enemy::TakeDamage(int damage) {
	Scene::AudioInstance.PlaySFX("Hurt");
	enemy.spritesheet.SetActiveAnimation("Hurt");

	int takeDamage = 0;

	if (info.status == Status::DEFFEND) {
		takeDamage = damage - (rand() % info.deffend + 1);
		if (takeDamage < 0) takeDamage = 0;
	}
	else {
		takeDamage = damage;
	}

	info.hp -= takeDamage;

	if (info.hp <= 0) {
		Scene::AudioInstance.PlaySFX("Death");
		info.hp = 0;
		enemy.spritesheet.SetBaseAnimation("Death");
		enemy.spritesheet.SetActiveAnimation("Death");
		Scene::sequenceInstance.gameOver = true;
		Scene::UIInstance.SetPlayerWin("You Win");
	}

	Scene::UIInstance.ActiveVFX("-" + to_string(takeDamage) + " HP", CharacterType::ENEMY, glm::vec3(1,0,0));
	Scene::UIInstance.UpdateHP(CharacterType::ENEMY, info.hp);
}

void Enemy::BuildEnemySprite() {
	enemy.BuildShader("spriteAnim.vert", "spriteAnim.frag", nullptr);

	enemy.ApplyTexture("spritesheet/enemyspritesheet.png", 6, 4);
	enemy.spritesheet.SetAnimationState("Idle", 140, 3, 3);
	enemy.spritesheet.SetActiveAnimation("Idle");
	enemy.spritesheet.SetBaseAnimation("Idle");

	enemy.spritesheet.SetAnimationState("Attack", 80, 4, 0, false);
	enemy.spritesheet.SetAnimationState("Death", 60, 6, 1, false);
	enemy.spritesheet.SetAnimationState("Hurt", 160, 2, 2, false);


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

	enemy.BuildObject(vertices, sizeof(vertices), indices, sizeof(indices));

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(Window::GetScreenWidth()), static_cast<GLfloat>(Window::GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	enemy.shader.UseShader();
	glUniformMatrix4fv(glGetUniformLocation(enemy.GetObjectShaderID(), "projection"), 1, GL_FALSE, value_ptr(projection));

	enemy.transform.Scale(vec3(-enemy.spritesheet.GetWidth() * 1.8f, enemy.spritesheet.GetHeight() * 1.8f, 1));

	// set sprite position, gravity, velocity
	//xpos = (Window::GetScreenWidth() - player.spritesheet.GetWidth());
	xpos = Window::GetScreenWidth() - enemy.spritesheet.GetWidth() + 280;
	yposGround = Window::GetScreenHeight() - (enemy.spritesheet.GetHeight() + 100);
	ypos = yposGround;
	gravity = 0.05f;
	xVelocity = 0.1f;

	enemy.transform.SetPosition(glm::vec3(xpos, ypos, 0));
}

void Enemy::DrawEnemySprite() {
	enemy.Render();
}

void Enemy::UpdateSpriteAnim() {
	enemy.Animate(enemy.spritesheet.GetActiveAnimation().name);
}