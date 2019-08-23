#include "PrintManager.h"
#include "PassengerManager.h"
#include <conio.h>

PrintManager printManager;
int fps = 30;

void Init()
{
	printManager.elevatorManager->Init();
	printManager.passengerManager->RandomSpawn();
}

void Update()
{
	int num = 0;
	while (num != 3)
	{
		system("cls");
		cout << "1 : 자동모드" << endl;
		cout << "2 : 수동모드" << endl;
		cout << "3 : 종료" << endl;
		cin >> num;

		if (num == 1)
		{
			int spawnCount = rand() % 5 + 1;
			printManager.Print();

			while (!_kbhit())
			{
				//!_kbhit()
				printManager.passengerManager->UpdatePassengers();
				printManager.elevatorManager->CheckButtons();

				printManager.Print();
				printManager.elevatorManager->UpdateElevators();

				if (spawnCount == 0)
				{
					for (int i = 0; i < rand() % 3 + 1; i++)
					{
						printManager.passengerManager->RandomSpawn();
					}
					printManager.passengerManager->RandomSpawn();
					spawnCount = rand() % 5 + 1;
					spawnCount = 5;
				}

				spawnCount--;
				_sleep(1000 / fps);
				//_getch();
			}
		}
		else if (num == 2)
		{
			int spawnCount = rand() % 5 + 1;
			printManager.Print();

			while (_getch())
			{
				//!_kbhit()
				printManager.passengerManager->UpdatePassengers();
				printManager.elevatorManager->CheckButtons();

				printManager.Print();
				printManager.elevatorManager->UpdateElevators();

				if (spawnCount == 0)
				{
					for (int i = 0; i < rand() % 3 + 1; i++)
					{
						printManager.passengerManager->RandomSpawn();
					}
					printManager.passengerManager->RandomSpawn();
					spawnCount = rand() % 5 + 1;
					spawnCount = 5;
				}

				spawnCount--;
				_sleep(1000 / fps);
				_getch();
			}
		}
	}
}

int main()
{
	Init();
	Update();
	return 0;
}