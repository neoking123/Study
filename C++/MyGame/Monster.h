#pragma once
#include <string>
#include "Scene.h"
using namespace std;

class Monster
{
public:
	string name;
	int hp;
	int atk;
	int def;
	int rewardExp;
	Position* position;
	Map* currentMap;
	
public:
	Monster();
	void Init(string name, int hp, int atk, int def, int rewardExp, Map* map);
	~Monster();
};

