#include "Student.h"

Student::Student(int _number, int _studentType, string _name, int _kor, int _eng, int _math)
{
	number = _number;
	studentType = _studentType; // 0이면 이과, 1이면 문과
	name.reserve(256);
	name = _name;
	kor = _kor;
	eng = _eng;
	math = _math;
}

Student::~Student()
{
}

void Student::SetScore(int _kor = 0, int _eng = 0, int _math = 0)
{
	kor = _kor;
	eng = _eng;
	math = _math;
}
