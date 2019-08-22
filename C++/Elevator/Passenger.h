#pragma once
#include <cstdlib>
#include <utility>
#include "ElevatorManager.h"

class Passenger
{
public:
	int weight;
	int floor;
	int targetFloor;
	int elevatorNum;
	bool pressBtn;
	bool isBoard;
	int waitTime;
	EDirection direction;
	ElevatorManager* elevatorManager;
	Elevator* closerElevatorIter;

public:
	Passenger();
	Passenger(int _weight = 0, int _floor = 0, int _targetFloor = 0, ElevatorManager* _elevatorManager = nullptr);
	~Passenger();

	// 엘리베이터 콜
	void CallElevator();
	// 버튼 누르기
	void PressButton(Elevator* _closerElevator);
	// 대기 시간 카운트
	void Waitting();
	// 가장 가까운 엘리베이터 찾기
	Elevator* FindCloserElevator();
};

