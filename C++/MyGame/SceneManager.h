#pragma once
#include "Player.h"

class SceneManager
{
private:
	Player* player;
	Monster* monster;

public:
	SceneManager();
	~SceneManager();

	vector<Scene*> scenes;
	ESceneType currentScene;

	void Init();
	void DrawScene();
	void SetPlayer(Player* player);
	void SetMonster(Monster* monster);
	Player* GetPlayer();
	void CheckPlayerPosition(Player& player);
};

