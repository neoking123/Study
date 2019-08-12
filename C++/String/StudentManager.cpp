#include "StudentManager.h"

StudentManager::StudentManager(int _classCount)
{
	classCount = _classCount;
	studentCount = 0;
}


StudentManager::~StudentManager()
{
}

void StudentManager::insertStudent(Student& student)
{
	students[studentCount] = student;
	studentCount++;
}

int StudentManager::CalAverage(int studentNum)
{
	
	return CalSum(studentNum) / 3;
}

int StudentManager::CalSum(int stuentNum)
{
	return students[stuentNum].eng + students[stuentNum].kor + students[stuentNum].math;
}

void StudentManager::printScoreBoard()
{
	cout << "번호\t이름\t국어\t영어\t수학\t평균\t총점" << endl;
	for (int i = 0; i < studentCount; i++)
	{
		cout << students[i].number << "\t" << students[i].name << "\t" << students[i].kor << "\t" << students[i].eng << "\t" << students[i].math << "\t" << CalAverage(i) << "\t" << CalSum(i) << endl;
	}
}
