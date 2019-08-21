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
	//		cout << "��";
	//	}
	//	else if (*iter == EmapType::ELEVATOR)
	//	{
	//		cout << "��";
	//	}
	//	else if (*iter == EmapType::PASSENGER)
	//	{
	//		cout << "��";
	//	}

	//	//cout << floorCount << "��"
	//}

	for (int i = 0; i < HEIGHT * WIDTH; i += WIDTH)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (building[i + j] == EmapType::WALL)
			{
				cout << "��";
			}
			else if (building[i + j] == EmapType::ELEVATOR)
			{
				cout << "��";
			}
			else if (building[i + j] == EmapType::PASSENGER)
			{
				cout << "��";
			}
		}

		for (vector<Elevator*>::iterator iter = elevatorManager.elevators.begin(); iter != elevatorManager.elevators.end(); iter++)
		{
			if ((*iter)->floor == floorCount)
			{
				cout << "��";
			}
		}

		floorCount--;
		cout << endl;
	}
}
