#include "STUDENT.h"

STUDENT::STUDENT(int _no)
{
	cout << "생성자 호출" << endl;
	cout << "생성자 호출" << endl;
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
	cout << "소멸자 호출" << endl;
	delete [] pOut;
}


void STUDENT::print()
{
	cout << aaa << endl;
}