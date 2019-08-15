#pragma once
#include "Scene.h"
#include "Player.h"

class SceneManager
{
private:
	Player* player;

public:
	SceneManager();
	~SceneManager();

	vector<Scene*> scenes;
	ESceneType currentScene;

	void Init();
	void DrawScene();
	void CheckPlayerPosition(Player& player);
};

