#include "Scene.h"

Scene::Scene() {
	player = CharacterController();
	object = StaticObject();
}

Scene::~Scene() {

}

void Scene::Init() {
	object.Init();
	player.Init();
}

void Scene::Update() {
	object.Update();
	player.Update();
}

void Scene::Render() {
	object.Render();
	player.Render();
}