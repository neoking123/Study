#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	int num = 0; // stack

	// 숫자 한개 입력 받고
	// 입력받은 숫자만큼 동적 공간 할당
	// 출력

	cin >> num;
	int *count = new int[num];

	for (int i = 0; i < num; i++)
	{
		cin >> count[i];
	}

	for (int i = 0; i < num; i++)
	{
		cout << count[i] << " ";
	}

	delete[] count;

	return 0;
}