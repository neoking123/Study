#include <iostream>
#include <time.h>
using namespace std;

int userInput[3];
int computerNum[3];
int ballCount = 0;
int strikeCount = 0;
int tryCount = 0;
bool quit = false;

void RandomNumber()
{
	for (int i = 0; i < 3; i++)
	{
		computerNum[i] = rand() % 10;
		while (i == 1)
		{
			if (computerNum[i] == computerNum[i - 1])
			{
				computerNum[i] = rand() % 10;
			}
			else
				break;
		}
		while (i == 2)
		{
			if (computerNum[i] == computerNum[i - 1] || computerNum[i] == computerNum[i - 2])
			{
				computerNum[i] = rand() % 10;
			}
			else
				break;
		}
	}
}

void input()
{
	tryCount++;
	ballCount = 0;
	strikeCount = 0;
	for (int i = 0; i < 3; i++)
	{
		cin >> userInput[i];
	}
}

void Init()
{
	srand(time(nullptr));
}

void Check()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (computerNum[i] == userInput[j] && i == j)
			{
				strikeCount++;
			}
			else if(computerNum[i] == userInput[j] && i != j)
			{
				ballCount++;
			}
		}
	}
	
	/*cout << endl;
	cout << "컴퓨터 숫자 : ";
	for (int i = 0; i < 3; i++)
	{
		cout << computerNum[i] << " ";
	}*/

	/*cout << endl;
	cout << "사용자 숫자 : ";
	for (int i = 0; i < 3; i++)
	{
		cout << userInput[i] << " ";
	}*/

	cout << endl;
	cout << endl;
	cout << tryCount << "턴" << endl;
	cout << "스트라이크 : " << strikeCount << endl;
	cout << "볼 : " << ballCount << endl;
	cout << endl;

	if (strikeCount == 3)
	{
		cout << "승리!" << endl;
		quit = true;
	}
}

int main()
{
	Init();
	RandomNumber();

	while (!quit)
	{
		input();
		Check();
	}

	return 0;
}