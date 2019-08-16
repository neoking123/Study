#pragma once
#include "..\MapEditor\Map.h"

class Player;
class Monster;
class Boss;

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
	int mapWidth;
	int mapHeight;

	void printTitle();		  // 타이틀
	void printIntro();		  // 인트로
	void printEnd();		  // 엔딩
	void printMenu();		  // 게임 메뉴
	void printField();	  	  // 필드
	void printPlayerMenu();	  // 플레이어 메뉴
	//void printBattleStart()	; // 전투 시작
	void printBattleLog(string newBattleLog); // 전투 로그
	void printBattleMenu();	  // 전투 메뉴
	void printBattleIng();	  // 전투 상태
	void printBattleEnd();	  // 전투 종료

public:
	Scene();
	Scene(ESceneType sceneType);
	~Scene();

	Player* player;
	Monster* monster;
	Boss* boss;
	vector<Map*> maps;
	EMap currentMapName;
	ESceneType sceneType;

	void Draw();
	bool LoadMap(string fileName);

};

