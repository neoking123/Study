#include <iostream>
#include "SingleTone.h"
using namespace std;

// �̱��� ���� : �������������� ���� ����
//int currentMap[20];

int main()
{
	int a = SingleTone::GetInstance()->map[10];

	return 0;
}