#pragma once
#include "Student.h"
#include "ScienceStudent.h"
#include "HumanityStudent.h"
#include <vector>

class Student;

class StudentManager
{
private:
	//Student students[256];
	vector<Student*> students;
	int classCount;
	int studentCount;

public:
	StudentManager(int _classCount = 0);
	~StudentManager();

	void insertStudent(Student* student);
	int CalAverage(int studentNum);
	int CalSum(int stuentNum);
	void printScoreBoard();
};

