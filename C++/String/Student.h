#pragma once
#include <string>
#include <iostream>
using namespace std;

class Student
{
public:
	int number;
	string name;
	int kor;
	int eng;
	int math;

	Student(int _number = 0, string _name = "", int _kor = 0, int _eng = 0, int _math = 0); // ������� ����Ʊ�� ����
	~Student();

	void SetScore(int _kor, int _eng, int _math);
};

