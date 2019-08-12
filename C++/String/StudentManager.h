#pragma once
#include "Student.h"

class Student;

class StudentManager
{
private:
	Student students[256];
	int classCount;
	int studentCount;

public:
	StudentManager(int _classCount = 0);
	~StudentManager();

	void insertStudent(Student& student);
	int CalAverage(int studentNum);
	int CalSum(int stuentNum);
	void printScoreBoard();
};

