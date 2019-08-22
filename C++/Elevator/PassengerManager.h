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

public:
	PassengerManager();
	~PassengerManager();

	void RandomSpawn();
	void UpdatePassengers();
	void CheckCanBoard(Passenger* _passenger, int _elevatorNum);
	void GetOffPassenger(list<Passenger*>::iterator _passenger);
	list<Passenger*>::iterator CheckGetOff(list<Passenger*>::iterator _passenger, int _elevatorNum);
	void CarryPassenger(Passenger* _passenger);
	void OffButtion(Passenger* _passenger, int _elevatorNum);
};

