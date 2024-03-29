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

void StudentManager::insertStudent(Student& student)
{
	//students[studentCount] = student;
	students.push_back(make_shared<Student>(student));
	studentCount++;
}

void StudentManager::NewStudent(int _studentType, string _name, int _kor, int _eng, int _math)
{
	if (_studentType == 0)
	{
		int _math2;
		cin >> _math2;
		students.push_back(make_shared<ScienceStudent>(new ScienceStudent(studentCount, _studentType, _name, _kor, _eng, _math, _math2)));
		studentCount++;
	}
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

	for (vector<shared_ptr<Student>>::iterator iter = students.begin(); iter != students.end(); iter++)
	{
		if ((*iter)->studentType == 0)
		{
			
			ScienceStudent* pCh = dynamic_cast<ScienceStudent*>(iter->get());
			if(pCh)
				cout << (*iter)->number << "\t" << (*iter)->name << "\t" << (*iter)->kor << "\t" << (*iter)->eng << "\t" << (*iter)->math << "\t" << pCh->math2 << "\t" << 0 << "\t" << ((*iter)->kor + (*iter)->eng + (*iter)->math + pCh->math2) / 4 << "\t" << (*iter)->kor + (*iter)->eng + (*iter)->math + pCh->math2 << "\t이과" << endl;
		}
		else if ((*iter)->studentType == 1)
		{
			HumanityStudent* pCh = dynamic_cast<HumanityStudent*>(iter->get());
			if (pCh)
				cout << (*iter)->number << "\t" << (*iter)->name << "\t" << (*iter)->kor << "\t" << (*iter)->eng << "\t" << (*iter)->math << "\t" << 0 << "\t" << pCh->history << "\t" << ((*iter)->kor + (*iter)->eng + (*iter)->math + pCh->history) / 4 << "\t" << (*iter)->kor + (*iter)->eng + (*iter)->math + pCh->history << "\t문과" << endl;
		}
	}
}

void StudentManager::SortStudent()
{
	sort(students.begin(), students.end(), [](shared_ptr<Student> stu1, shared_ptr<Student> stu2)->bool{ return stu1->kor > stu2->kor; });
}
