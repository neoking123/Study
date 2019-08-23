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
			cout << "�� " << floorCount << "�� ��  ";
		}
		else
		{
			cout << "��  " << floorCount << "�� ��  ";
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
					cout << "[��";
				}
				else if ((*iter)->num == 2)
				{
					cout << "[��";
				}
				else if ((*iter)->num == 3)
				{
					cout << "[��";
				}
				else if ((*iter)->num == 4)
				{
					cout << "[��";
				}

				if ((*iter)->direction == EDirection::Stop)
				{
					cout << "��]";
				}
				else if ((*iter)->direction == EDirection::UP)
				{
					cout << "��]";
				}
				else if ((*iter)->direction == EDirection::Down)
				{
					cout << "��]";
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
				cout << "[��" << (*iter)->waitTime << "]";
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
	cout << "����������" << endl;
	for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
	{
		cout << (*iter)->num << "��, ������ : " << (*iter)->floor << ", ��ǥ�� : " << (*iter)->targetFloor 
			<< ", ž���ο� : " << (*iter)->CurrentPasssengerCount << ", �ѹ��� : "<< (*iter)->CurrentWeight <<endl;
	}

	cout << endl;
	cout << "ž���� ��� ��� �ð� : " << passengerManager->GetAvgWaitTime() << endl;
	

	cout << endl;
	cout << "ž����" << endl;
	for (list<Passenger*>::iterator iter = passengerManager->passengers.begin(); iter != passengerManager->passengers.end(); iter++)
	{
		cout << "������ : " << (*iter)->floor << ", ��ǥ�� : " << (*iter)->targetFloor << endl;
		if ((*iter)->elevatorNum > 0)
		{
			cout << (*iter)->elevatorNum << "�� ���������� ž��" << endl << endl;
		}
		else
		{
			cout << endl << endl;
		}
	}
}
