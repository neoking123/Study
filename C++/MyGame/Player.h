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

	void Init(string name, int hp, int mp, int atk, int def, int exp, int level, Map* map);
	string GetName();
	int GetHp();
	int GetMp();
	int GetAtk();
	int GetDef();
	int GetExp();
	int GetLevel();
	void SetHp(int newHp);
	void SetMp(int newMp);
	EKey Input();
	void ChangeMap(Map* map, EMap currentMapName);
};

