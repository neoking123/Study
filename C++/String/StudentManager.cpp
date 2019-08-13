#include "StudentManager.h"

StudentManager::StudentManager(int _classCount)
{
	classCount = _classCount;
	studentCount = 0;
	students.reserve(100);
}


StudentManager::~StudentManager()
{
}

void StudentManager::insertStudent(Student* student)
{
	//students[studentCount] = student;
	students.push_back(student);
	studentCount++;
}

int StudentManager::CalAverage(int studentNum)
{
	
	return CalSum(studentNum) / 3;
}

int StudentManager::CalSum(int stuentNum)
{
	return students[stuentNum]->eng + students[stuentNum]->kor + students[stuentNum]->math;
}

void StudentManager::printScoreBoard()
{
	cout << "번호\t이름\t국어\t영어\t수학\t수학2\t역사\t평균\t총점\t비고" << endl;
	/*for (int i = 0; i < studentCount; i++)
	{
		cout << students[i].number << "\t" << students[i].name << "\t" << students[i].kor << "\t" << students[i].eng << "\t" << students[i].math << "\t" << CalAverage(i) << "\t" << CalSum(i) << endl;
	}*/

	for (vector<Student*>::iterator iter = students.begin(); iter != students.end(); iter++)
	{
		if ((*iter)->studentType == 0)
		{
			ScienceStudent* pCh = dynamic_cast<ScienceStudent*>(*iter);
			if(pCh)
				cout << (*iter)->number << "\t" << (*iter)->name << "\t" << (*iter)->kor << "\t" << (*iter)->eng << "\t" << (*iter)->math << "\t" << pCh->math2 << "\t" << 0 << "\t" << ((*iter)->kor + (*iter)->eng + (*iter)->math + pCh->math2) / 4 << "\t" << (*iter)->kor + (*iter)->eng + (*iter)->math + pCh->math2 << "\t이과" << endl;
		}
		else if ((*iter)->studentType == 1)
		{
			HumanityStudent* pCh = dynamic_cast<HumanityStudent*>(*iter);
			if (pCh)
				cout << (*iter)->number << "\t" << (*iter)->name << "\t" << (*iter)->kor << "\t" << (*iter)->eng << "\t" << (*iter)->math << "\t" << 0 << "\t" << pCh->history << "\t" << ((*iter)->kor + (*iter)->eng + (*iter)->math + pCh->history) / 4 << "\t" << (*iter)->kor + (*iter)->eng + (*iter)->math + pCh->history << "\t문과" << endl;
		}
	}
}
