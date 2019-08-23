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
	delete elevatorManager;
	delete passengerManager;
}

void PrintManager::Print()
{
	system("cls");
	/*COORD Cur;
	Cur.X = 0;
	Cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);*/

	int floorCount = 20;

	for (int i = 0; i < HEIGHT * WIDTH; i += WIDTH)
	{
		if (floorCount >= 10)
		{
			cout << "¢É " << floorCount << "Ãþ ¢É  ";
		}
		else
		{
			cout << "¢É  " << floorCount << "Ãþ ¢É  ";
		}
		for (int j = 0; j < WIDTH; j++)
		{
			if (building[i + j] == EmapType::WALL)
			{
				cout << "";
			}
		}

		for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
		{
			if ((*iter)->floor == floorCount)
			{
				if ((*iter)->num == 1)
				{
					cout << "[¨ç";
				}
				else if ((*iter)->num == 2)
				{
					cout << "[¨è";
				}
				else if ((*iter)->num == 3)
				{
					cout << "[¨é";
				}
				else if ((*iter)->num == 4)
				{
					cout << "[¨ê";
				}

				if ((*iter)->direction == EDirection::Stop)
				{
					cout << "¢Á]";
				}
				else if ((*iter)->direction == EDirection::UP)
				{
					cout << "¡è]";
				}
				else if ((*iter)->direction == EDirection::Down)
				{
					cout << "¡é]";
				}
			}
			else
			{
				cout << "      ";
			}
		}
		cout << "  ";

		for (list<Passenger*>::iterator iter = passengerManager->passengers.begin(); iter != passengerManager->passengers.end(); iter++)
		{
			if ((*iter)->floor == floorCount)
			{
				cout << "[¿Ê" << (*iter)->waitTime << "]";
			}
			else
			{
				cout << "\t    ";
			}
		}

		floorCount--;
		cout << endl;
	}

	cout << endl;
	cout << "¿¤¸®º£ÀÌÅÍ" << endl;
	for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
	{
		cout << (*iter)->num << "¹ø, ÇöÀçÃþ : " << (*iter)->floor << ", ¸ñÇ¥Ãþ : " << (*iter)->targetFloor 
			<< ", Å¾½ÂÀÎ¿ø : " << (*iter)->CurrentPasssengerCount << ", ÃÑ¹«°Ô : "<< (*iter)->CurrentWeight <<endl;
	}

	cout << endl;
	cout << "Å¾½ÂÀÚ Æò±Õ ´ë±â ½Ã°£ : " << passengerManager->GetAvgWaitTime() << endl;
	

	cout << endl;
	cout << "Å¾½ÂÀÚ" << endl;
	for (list<Passenger*>::iterator iter = passengerManager->passengers.begin(); iter != passengerManager->passengers.end(); iter++)
	{
		cout << "ÇöÀçÃþ : " << (*iter)->floor << ", ¸ñÇ¥Ãþ : " << (*iter)->targetFloor << endl;
		if ((*iter)->elevatorNum > 0)
		{
			cout << (*iter)->elevatorNum << "¹ø ¿¤¸®º£ÀÌÅÍ Å¾½Â" << endl << endl;
		}
		else
		{
			cout << endl << endl;
		}
	}
}
