#include "STUDENT.h"

STUDENT::STUDENT(int _no)
{
	cout << "������ ȣ��" << endl;
	cout << "������ ȣ��" << endl;
	no = _no;
	memset(szNum, 0, 256);
	pOut = new char[256];
}

STUDENT::STUDENT(const STUDENT& other)
{
	no = other.no;
	pOut = new char[256]; // deep copy
	strcpy(pOut, other.pOut);
}


STUDENT::~STUDENT()
{
	cout << "�Ҹ��� ȣ��" << endl;
	delete [] pOut;
}


void STUDENT::print()
{
	cout << aaa << endl;
}