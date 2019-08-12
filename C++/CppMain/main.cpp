#include <iostream>
#include "Map.h"
#include "Player.h"
using namespace std;

int main()
{
	Player player;
	Map map;

	map.Init();
	player.Init(map);
	map.Draw();

	while (true)
	{
		player.input(map);
		map.Draw();
	}

	return 0;
}