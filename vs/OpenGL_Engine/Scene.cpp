#include "Scene.h"

Scene::Scene() {
	player = CharacterController();
	object = StaticObject();
	enemy = Enemy();
}

Scene::~Scene() {

}

SequenceManager Scene::sequenceInstance;
UIManager Scene::UIInstance;
AudioManager Scene::AudioInstance;

void Scene::Init() {
	AudioInstance.Init();
	UIInstance.Init();
	object.Init();
	player.Init();
	enemy.Init();
	sequenceInstance.Init(player, enemy);	
	AudioInstance.PlayBGM();
}

void Scene::Update() {
	object.Update();
	player.Update();
	enemy.Update();
	sequenceInstance.ExecuteSequence();
	UIInstance.Update();	

	if (sequenceInstance.gameOver && !object.transparentPanel.activeSelf) {
		object.transparentPanel.activeSelf = true;
	}
}

void Scene::Render() {
	object.Render();
	player.Render();
	enemy.Render();
	UIInstance.Render();
	object.LateRender();
	if (sequenceInstance.gameOver) {
		UIInstance.GameOverRender();
	}
}