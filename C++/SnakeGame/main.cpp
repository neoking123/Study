#include "Player.h"

#define FPS 30

int main()
{
	int enemyCount = 5;
	Map map;
	map.Init();
	map.SetMap();

	for (int i = 0; i < enemyCount; i++)
	{
		map.SpawnEnemy();
	}

	Player player;
	player.Init(map);

	while (!player.death)
	{
		map.Draw();
		player.MoveDirection(map);
		_sleep(1000 / FPS);
	}

	cout << endl;
	cout << "\t\t\t\t¡ØGAME OVER¡Ø" << endl;
	cout << "\t\t\t\tScore : " << player.PrintNodeCount() << endl;

	return 0;
}