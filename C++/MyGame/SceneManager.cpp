#include "SceneManager.h"

SceneManager::SceneManager()
{
	currentScene = ESceneType::NONE;
	player = nullptr;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	scenes.reserve(10);

	for (int i = 0; i < 8; i++)
	{
		Scene* newScene = new Scene((ESceneType)i);
		scenes.push_back(newScene);
	}
	
	/*scenes.push_back(new Scene(ESceneType::NONE));
	scenes.push_back(new Scene(ESceneType::TITLE));
	scenes.push_back(new Scene(ESceneType::MENU));
	scenes.push_back(new Scene(ESceneType::INTRO));
	scenes.push_back(new Scene(ESceneType::END));
	scenes.push_back(new Scene(ESceneType::FIELD));
	scenes.push_back(new Scene(ESceneType::BATTLE));
	scenes.push_back(new Scene(ESceneType::PLAYERMENU));*/
}

void SceneManager::DrawScene()
{
	scenes[currentScene]->Draw();
}

void SceneManager::SetPlayer(Player* player)
{
	this->player = player;
}

void SceneManager::SetMonster(Monster * monster)
{
	this->monster = monster;
}

Player* SceneManager::GetPlayer()
{
	return this->player;
}

void SceneManager::CheckPlayerPosition(Player& player)
{
	if (player.position->mapState == EMapState::PO_VIL_BA)
	{
		player.position->bPlayer = false;
		player.ChangeMap(scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE], EMap::BATTLEZONE);
		player.position = scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE]->GetPosition(1, 16);
		player.position->bPlayer = true;
		scenes[currentScene]->currentMapName = EMap::BATTLEZONE;
		
	}
	else if (player.position->mapState == EMapState::PO_BA_VIL)
	{
		player.position->bPlayer = false;
		player.ChangeMap(scenes[ESceneType::FIELD]->maps[EMap::VILLAGE], EMap::VILLAGE);
		player.position = scenes[ESceneType::FIELD]->maps[EMap::VILLAGE]->GetPosition(38, 16);
		player.position->bPlayer = true;
		scenes[currentScene]->currentMapName = EMap::VILLAGE;
	}
	else if (player.position->mapState == EMapState::PO_BA_BO)
	{
		player.position->bPlayer = false;
		player.ChangeMap(scenes[ESceneType::FIELD]->maps[EMap::BOSSROOM], EMap::BOSSROOM);
		player.position = scenes[ESceneType::FIELD]->maps[EMap::BOSSROOM]->GetPosition(1, 3);
		player.position->bPlayer = true;
		scenes[currentScene]->currentMapName = EMap::BOSSROOM;
	}
	else if (player.position->mapState == EMapState::PO_BO_BA)
	{
		player.position->bPlayer = false;
		player.ChangeMap(scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE], EMap::BATTLEZONE);
		player.position = scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE]->GetPosition(38, 3);
		player.position->bPlayer = true;
		scenes[currentScene]->currentMapName = EMap::BATTLEZONE;
	}
	else if (player.position->bMonster)
	{
		currentScene = ESceneType::BATTLE;
		scenes[currentScene]->monster = monster;
		scenes[currentScene]->player = this->player;
	}
}
