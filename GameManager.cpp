#include"Field.hpp"
#include"FieldControl.hpp"
#include"BaseScene.h"
#include"TitleScene.h"
#include"GameScene.h"
#include "GameManager.h"



GameManager::GameManager()
{
	scene = new TitleScene;
}


GameManager::~GameManager()
{
	delete scene;
}

void GameManager::Run() {
	while (true) {
		if (!scene->Update()) {
			TransGame();
			break;
		}
	}
	while (true) {
		if (!scene->Update()) break;
	}
}

void GameManager::TransGame() {
	delete scene;
	scene = new GameScene;
}