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
	//������ ����� ���������� Ž��
	Elevator* FindElevator(int _floor);
	//������ ����� ���������͸� ������ �������� ����� ���������� Ž��
	Elevator* FindElevatorAnother(int _floor, Elevator* _anotherCloserElevator);
};

