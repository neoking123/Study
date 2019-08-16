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
	TITLE,		// ���� Ÿ��Ʋ
	MENU,		// ���� �޴�
	INTRO,		// ��Ʈ��
	END,		// ����
	FIELD,		// ������
	BATTLE,		// ����
	PLAYERMENU  // �÷��̾� �޴�
};

class Scene
{
private:
	int mapWidth;
	int mapHeight;

	void printTitle();		  // Ÿ��Ʋ
	void printIntro();		  // ��Ʈ��
	void printEnd();		  // ����
	void printMenu();		  // ���� �޴�
	void printField();	  	  // �ʵ�
	void printPlayerMenu();	  // �÷��̾� �޴�
	//void printBattleStart()	; // ���� ����
	void printBattleLog(string newBattleLog); // ���� �α�
	void printBattleMenu();	  // ���� �޴�
	void printBattleIng();	  // ���� ����
	void printBattleEnd();	  // ���� ����

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

