#include <iostream>
#include "SingleTone.h"
using namespace std;

// 싱글톤 패턴 : 전역변수용으로 많이 쓰임
//int map[20];

int main()
{
	int a = SingleTone::GetInstance()->map[10];


	return 0;
}