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

	// 탑승자 랜덤 스폰
	void RandomSpawn();
	// 탑승자 업데이트
	void UpdatePassengers();
	// 탑승 체크
	void CheckCanBoard(Passenger* _passenger, int _elevatorNum);
	// 하차 체크
	list<Passenger*>::iterator CheckGetOff(list<Passenger*>::iterator _passenger, int _elevatorNum);
	// 탑승자 운반
	void CarryPassenger(Passenger* _passenger);
	// 버튼 비활성화
	void OffButtion(Passenger* _passenger, int _elevatorNum);
};

