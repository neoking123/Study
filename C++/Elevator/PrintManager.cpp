#include "PrintManager.h"

PrintManager::PrintManager()
{
	building.reserve(1000);
	building.assign(400, 0);
	elevatorManager = new ElevatorManager();
	passengerManager = new PassengerManager();
	passengerManager->elevatorManager = elevatorManager;
}

PrintManager::~PrintManager()
{
}

void PrintManager::Print()
{
	system("cls");
	int floorCount = 20;

	for (int i = 0; i < HEIGHT * WIDTH; i += WIDTH)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (building[i + j] == EmapType::WALL)
			{
				cout << "¢É";
			}
		}

		for (list<Passenger*>::iterator iter = passengerManager->passengers.begin(); iter != passengerManager->passengers.end(); iter++)
		{
			if ((*iter)->floor == floorCount)
			{
				cout << "¿Ê";
			}
			else
			{
				cout << "  ";
			}
		}

		for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
		{
			if ((*iter)->floor == floorCount)
			{
				cout << "¡á";
			}
			else
			{
				cout << "  ";
			}
		}

		floorCount--;
		cout << endl;
	}

	cout << endl;
	cout << "¿¤¸®º£ÀÌÅÍ" << endl;
	for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
	{
		cout << (*iter)->num << "¹ø, ÇöÀçÃþ : " << (*iter)->floor << ", ¸ñÇ¥Ãþ : " << (*iter)->targetFloor << endl;
	}

	cout << endl;
	cout << "Å¾½ÂÀÚ" << endl;
	for (list<Passenger*>::iterator iter = passengerManager->passengers.begin(); iter != passengerManager->passengers.end(); iter++)
	{
		cout << "ÇöÀçÃþ : " << (*iter)->floor << ", ¸ñÇ¥Ãþ : " << (*iter)->targetFloor << endl;
		cout << (*iter)->elevatorNum << "¹ø ¿¤¸®º£ÀÌÅÍ Å¾½Â" << endl;
	}
}
