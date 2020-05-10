#include "Scene.h"

Scene::Scene() {
	player = CharacterController();
}

Scene::~Scene() {

}

void Scene::Init() {
	player.Init();
}

void Scene::Update() {
	player.Update();
}

void Scene::Render() {
	player.Render();
}