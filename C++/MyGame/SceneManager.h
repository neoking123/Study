#pragma once
#include "Player.h"
#include "Boss.h"

class SceneManager
{
private:
	Player* player;
	Monster* monster;
	Boss* boss;

public:
	SceneManager();
	~SceneManager();

	vector<Scene*> scenes;
	ESceneType currentScene;
	ESceneType prevtScene;

	void Init();
	void DrawScene();
	void SetPlayer(Player* player);
	void SetMonster(Monster* monster);
	void SetBoss(Boss* boss);
	Player* GetPlayer();
	void CheckPlayerPosition(Player& player);
	void CheckSceneType();
};

