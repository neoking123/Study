#pragma once
#include <string>
#include "Scene.h"
using namespace std;

class Player
{
private:
	string name;
	int hp;
	int mp;
	int atk;
	int def;
	int exp;
	int level;
	Map* currentMap;

public:
	Player();
	~Player();

	EMap currentMapName;
	Position* position;

	void Init(int hp, int mp, int atk, int def, int exp, int level, Map* map);
	int GetHp();
	int GetMp();
	void SetHp(int newHp);
	void SetMp(int newMp);
	void Input();
	void ChangeMap(Map* map, EMap currentMapName);
};

