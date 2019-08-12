#pragma once
#include <iostream>
using namespace std;

//int STUDENT::aaa = 0; // static 선언

class STUDENT
{
private:
	static int aaa; // 멤버 공유
	//static void AddPoint; // 전역 함수

	int no;
	char szNum[256];
	char* pOut;

	void print();

	STUDENT(int _no);
	STUDENT(const STUDENT& other);
	~STUDENT();

public:

	// 인라인 함수 헤더에서 작동, 간단한 함수에서 메모리 점프가 일어나지 않기위해 사용
	inline void SetNo(int _no)
	{
		no = _no;
	}
};

