// 성적표
// 학생 최대수 3명
// 1.입력
// 2.출력
// 3.저장
// 4.종료

// 출력
// 번호 이름 국 영 수 평균 총점

#include "pch.h"
#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

struct student
{
	int number = 0;
	char szName[128];
	int kor = 0;
	int eng = 0;
	int math = 0;
	float avg = 0;
	int sum = 0;
};

void PrintMenu()
{
	cout << "1.입력" << endl;
	cout << "2.출력" << endl;
	cout << "3.저장" << endl;
	cout << "4.종료" << endl;
	cout << "번호를 입력하세요 : ";
}

int main()
{
	int count = 0;
	int select = 0;

	student st[10];
	char szBuf[256];

	ofstream outFile("scoreBoard.txt");

	while (true)
	{
		PrintMenu();
		cin >> select;

		system("cls");

		if (select == 1)
		{
			cout << endl;
			cout << "이름을 입력하세요 : ";
			cin >> st[count].szName;

			cout << "국어 점수를 입력하세요 : ";
			cin >> st[count].kor;

			cout << "영어 점수를 입력하세요 : ";
			cin >> st[count].eng;

			cout << "수학 점수를 입력하세요 : ";
			cin >> st[count].math;

			st[count].number = count;
			st[count].sum = st[count].kor + st[count].eng + st[count].math;
			st[count].avg = st[count].sum / 3;

			count++;
		}
		else if (select == 2)
		{
			cout << endl;
			cout << "번호\t이름\t국어\t영어\t수학\t평균\t총점" << endl;
			
			//inFile >> szBuf;
			ifstream inFile("scoreBoard.txt");

			for (int i = 0; i < count; i++)
			{
				inFile.getline(szBuf, 256);
				cout << szBuf << endl;
			}
			
			/*for (int i = 0; i < count; i++)
			{
				cout << st[i].number << "\t" << st[i].szName 
					 << "\t" << st[i].kor << "\t" << st[i].eng 
					 << "\t" << st[i].math << "\t" << st[i].avg 
					 << "\t" << st[i].sum << endl;
			}*/
		}
		else if (select == 3)
		{
			for (int i = 0; i < count; i++)
			{
				outFile << st[i].number << "\t" << st[i].szName
					<< "\t" << st[i].kor << "\t" << st[i].eng
					<< "\t" << st[i].math << "\t" << st[i].avg
					<< "\t" << st[i].sum << endl;
			}
		}
		else if (select == 4)
		{
			break;
		}

		cout << endl;
	}

	return 0;
}