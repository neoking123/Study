#include "Player.h"

int main()
{
	int enemyCount = 1;
	int Speed = 1;
	int fps = 60;
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
		player.SetScore();
		cout << endl;
		cout << "\t\t\t\tScore : " << player.GetScore() << endl;
		//_sleep(1000 / fps);
	}

	cout << endl;
	cout << "\t\t\t\t¡ØGAME OVER¡Ø" << endl;

	while (_getch() != 'q')
	{

	}

	return 0;
}