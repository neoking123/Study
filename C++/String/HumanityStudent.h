#pragma once
#include "Student.h"

class HumanityStudent : public Student
{
public:
	int history;

	virtual void SetScore(int _kor, int _eng, int _math, int _history);

	HumanityStudent(int _number = 0, int _studentType = 1, string _name = "", int _kor = 0, int _eng = 0, int _math = 0, int _history = 0);
	~HumanityStudent();
};

