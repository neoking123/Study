#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Elevator.h"
using namespace std;

class Button
{
public:
	ButtonType btn;
};

class ElevatorManager
{
public:
	vector<Elevator*> elevators;
	vector<Button> buttons;
	int elevatorCount;

public:
	ElevatorManager();
	~ElevatorManager();

	void PushBack(int _floor = 0, int _weightMax = 0, int _passengerMax = 0);
	void Init();
	void UpdateElevators();
	void CheckButtons();
	//층에서 가까운 엘리베이터 탐색
	Elevator* FindElevator(int _floor);
	//층에서 가까운 엘리베이터를 제외한 다음으로 가까운 엘리베이터 탐색
	Elevator* FindElevatorAnother(int _floor, Elevator* _anotherCloserElevator);
};

