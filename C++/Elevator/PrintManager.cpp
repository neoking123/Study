#include "PrintManager.h"



PrintManager::PrintManager()
{
	building.reserve(1000);
	building.assign(400, 0);
	elevatorManager.Init();
}


PrintManager::~PrintManager()
{
}

void PrintManager::Print()
{
	int floorCount = 20;
	//for (vector<int>::iterator iter = building.begin(); iter != building.end(); iter++)
	//{
	//	if (*iter == EmapType::WALL)
	//	{
	//		cout << "¢É";
	//	}
	//	else if (*iter == EmapType::ELEVATOR)
	//	{
	//		cout << "¡â";
	//	}
	//	else if (*iter == EmapType::PASSENGER)
	//	{
	//		cout << "¢»";
	//	}

	//	//cout << floorCount << "Ãþ"
	//}

	for (int i = 0; i < HEIGHT * WIDTH; i += WIDTH)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (building[i + j] == EmapType::WALL)
			{
				cout << "¢É";
			}
			else if (building[i + j] == EmapType::ELEVATOR)
			{
				cout << "¡â";
			}
			else if (building[i + j] == EmapType::PASSENGER)
			{
				cout << "¢»";
			}
		}

		for (vector<Elevator*>::iterator iter = elevatorManager.elevators.begin(); iter != elevatorManager.elevators.end(); iter++)
		{
			if ((*iter)->floor == floorCount)
			{
				cout << "¡â";
			}
		}

		floorCount--;
		cout << endl;
	}
}
