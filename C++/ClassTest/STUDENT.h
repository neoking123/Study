#pragma once
#include <iostream>
using namespace std;

//int STUDENT::aaa = 0; // static ����

class STUDENT
{
private:
	static int aaa; // ��� ����
	//static void AddPoint; // ���� �Լ�

	int no;
	char szNum[256];
	char* pOut;

	void print();

	STUDENT(int _no);
	STUDENT(const STUDENT& other);
	~STUDENT();

public:

	// �ζ��� �Լ� ������� �۵�, ������ �Լ����� �޸� ������ �Ͼ�� �ʱ����� ���
	inline void SetNo(int _no)
	{
		no = _no;
	}
};

