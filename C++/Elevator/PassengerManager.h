#pragma once
#include "Passenger.h"
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <time.h>
using namespace std;

class PassengerManager
{
public:
	list<Passenger*> passengers;
	ElevatorManager* elevatorManager;
	int passengerNum;
	int exitPassengerCount;
	int sumBoardTime;

public:
	PassengerManager();
	~PassengerManager();

	// ž���� ���� ����
	void RandomSpawn();
	// ž���� ������Ʈ
	void UpdatePassengers();
	// ž�� üũ
	void CheckCanBoard(Passenger* _passenger);
	// ž��
	void BoardElevator(Passenger* _passenger, vector<Elevator*>::iterator iter);
	// ���� üũ
	list<Passenger*>::iterator CheckGetOff(list<Passenger*>::iterator _passenger, int _elevatorNum);
	// ž���� ���
	void CarryPassenger(Passenger* _passenger);
	// ��ư ��Ȱ��ȭ
	void OffButtion(Passenger* _passenger);
	// ��� ž�� ��� �ð�
	float GetAvgWaitTime();
};

