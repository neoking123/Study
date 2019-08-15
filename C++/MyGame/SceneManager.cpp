#include "SceneManager.h"

SceneManager::SceneManager()
{
	currentScene = ESceneType::NONE;
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	scenes.push_back(new Scene(ESceneType::NONE));
	scenes.push_back(new Scene(ESceneType::TITLE));
	scenes.push_back(new Scene(ESceneType::MENU));
	scenes.push_back(new Scene(ESceneType::INTRO));
	scenes.push_back(new Scene(ESceneType::END));
	scenes.push_back(new Scene(ESceneType::FIELD));
	scenes.push_back(new Scene(ESceneType::BATTLE));
	scenes.push_back(new Scene(ESceneType::PLAYERMENU));
}

void SceneManager::DrawScene()
{
	scenes[currentScene]->Draw();
}

void SceneManager::CheckPlayerPosition(Player& player)
{
	if (player.position->mapState == EMapState::PO_VIL_BA)
	{
		player.position->bPlayer = false;
		player.ChangeMap(scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE], EMap::BATTLEZONE);
		player.position = scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE]->GetPosition(2, 16);
		player.position->bPlayer = true;
		scenes[currentScene]->currentMapName = EMap::BATTLEZONE;
		
	}
	else if (player.position->mapState == EMapState::PO_BA_VIL)
	{
		player.position->bPlayer = false;
		player.ChangeMap(scenes[ESceneType::FIELD]->maps[EMap::VILLAGE], EMap::VILLAGE);
		player.position = scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE]->GetPosition(38, 16);
		player.position->bPlayer = true;
		scenes[currentScene]->currentMapName = EMap::VILLAGE;
	}
}
