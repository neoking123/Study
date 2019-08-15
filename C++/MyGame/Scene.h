#pragma once
#include "..\MapEditor\Map.h"

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
	ESceneType sceneType;
	int mapWidth;
	int mapHeight;

	void printTitle();
	void printIntro();
	void printEnd();
	void printMenu();
	void printField();

public:
	Scene();
	Scene(ESceneType sceneType);
	~Scene();

	vector<Map*> maps;
	EMap currentMapName;

	void Draw();
	bool LoadMap(string fileName);
};

