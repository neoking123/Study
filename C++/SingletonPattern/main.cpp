#include <iostream>
#include "SingleTone.h"
using namespace std;

// �̱��� ���� : �������������� ���� ����
//int map[20];

int main()
{
	int a = SingleTone::GetInstance()->map[10];


	return 0;
}