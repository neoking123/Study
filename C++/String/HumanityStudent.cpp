#include "HumanityStudent.h"

void HumanityStudent::SetScore(int _kor, int _eng, int _math, int _history)
{
	Student::SetScore(_kor, _eng, _math);
	history = _history;
}

HumanityStudent::HumanityStudent(int _number, int _studentType, string _name, int _kor, int _eng, int _math, int _history)
	:Student(_number, _studentType, _name, _kor, _eng, _math)
{
	//Student::Student(_number, _studentType, _name, _kor, _eng, _math);
	//studentType = _studentType; // 0이면 이과, 1이면 문과
	/*Student::studentType = _studentType;
	number = _number;
	name.reserve(256);
	name = _name;
	kor = _kor;
	eng = _eng;
	math = _math;*/
	history = _history;
}

HumanityStudent::~HumanityStudent()
{
}
