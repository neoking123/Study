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
	cout << "��ȣ\t�̸�\t����\t����\t����\t���\t����" << endl;
	for (int i = 0; i < studentCount; i++)
	{
		cout << students[i].number << "\t" << students[i].name << "\t" << students[i].kor << "\t" << students[i].eng << "\t" << students[i].math << "\t" << CalAverage(i) << "\t" << CalSum(i) << endl;
	}
}
