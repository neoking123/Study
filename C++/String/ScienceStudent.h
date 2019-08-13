#pragma once
#include "Student.h"

class ScienceStudent : public Student
{
public:
	int math2;

	virtual void SetScore(int _kor, int _eng, int _math, int _math2);

	ScienceStudent(int _number = 0, int _studentType = 0, string _name = "", int _kor = 0, int _eng = 0, int _math = 0, int _math2 = 0);
	~ScienceStudent();
};

