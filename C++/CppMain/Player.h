#pragma once
#include <iostream>
#include <conio.h>
#include "Map.h"

class Map;
class Player
{
private:
	int x;
	int y;
public:
	Player();
	~Player();

	void Init(Map& map);
	void input(Map& map);
};

