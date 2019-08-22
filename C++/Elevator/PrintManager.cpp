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
				cout << "��";
			}
		}

		for (list<Passenger*>::iterator iter = passengerManager->passengers.begin(); iter != passengerManager->passengers.end(); iter++)
		{
			if ((*iter)->floor == floorCount)
			{
				cout << "��";
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
				cout << "��";
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
	cout << "����������" << endl;
	for (vector<Elevator*>::iterator iter = elevatorManager->elevators.begin(); iter != elevatorManager->elevators.end(); iter++)
	{
		cout << (*iter)->num << "��, ������ : " << (*iter)->floor << ", ��ǥ�� : " << (*iter)->targetFloor << endl;
	}

	cout << endl;
	cout << "ž����" << endl;
	for (list<Passenger*>::iterator iter = passengerManager->passengers.begin(); iter != passengerManager->passengers.end(); iter++)
	{
		cout << "������ : " << (*iter)->floor << ", ��ǥ�� : " << (*iter)->targetFloor << endl;
		cout << (*iter)->elevatorNum << "�� ���������� ž��" << endl;
	}
}
