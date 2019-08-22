#include "PrintManager.h"
#include "PassengerManager.h"
#include <conio.h>

PrintManager printManager;
int fps = 10;

void Init()
{
	printManager.elevatorManager->Init();
	printManager.passengerManager->RandomSpawn();

}

void Update()
{
	int spawnCount = rand() % 5 + 1;
	printManager.Print();
	while (true)
	{
		printManager.passengerManager->UpdatePassengers();
		printManager.elevatorManager->CheckButtons();
		
		printManager.Print();
		printManager.elevatorManager->UpdateElevators();

		if (spawnCount == 0)
		{
			printManager.passengerManager->RandomSpawn();
			spawnCount = rand() % 5 + 1;
		}
		spawnCount--;
		_sleep(1000 / fps);
		//_getch();
	}
}

int main()
{
	Init();
	Update();
	return 0;
}