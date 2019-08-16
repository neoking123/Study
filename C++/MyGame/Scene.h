#pragma once
#include "..\MapEditor\Map.h"

class Player;
class Monster;

enum EMap
{
	VILLAGE,
	BATTLEZONE,
	BOSSROOM
};

enum ESceneType
{
	NONE,
	TITLE,		// 메인 타이틀
	MENU,		// 게임 메뉴
	INTRO,		// 인트로
	END,		// 엔딩
	FIELD,		// 비전투
	BATTLE,		// 전투
	PLAYERMENU  // 플레이어 메뉴
};

class Scene
{
private:
	
	ESceneType sceneType;
	int mapWidth;
	int mapHeight;

	void printTitle();
	void printIntro();
	void printEnd();
	void printMenu();
	void printField();
	void printPlayerMenu();
	void printBattleStart(); // 전투 시작 씬
	void printBattleIng(); // 전투 상태 씬

public:
	Scene();
	Scene(ESceneType sceneType);
	~Scene();

	Player* player;
	Monster* monster;
	vector<Map*> maps;
	EMap currentMapName;

	void Draw();
	bool LoadMap(string fileName);
};

