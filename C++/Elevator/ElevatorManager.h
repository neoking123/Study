#pragma once
#include <vector>
#include <memory>
#include "Elevator.h"
using namespace std;

class ElevatorManager
{
public:
	//vector<shared_ptr<Elevator>> Elevators;
	vector<Elevator*> elevators;
	int elevatorCount;

public:
	ElevatorManager();
	~ElevatorManager();

	void push_back(int _floor = 0, int _weightMax = 0, int _passengerMax = 0);
	void Init();
};

