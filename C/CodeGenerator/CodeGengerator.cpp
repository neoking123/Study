#include <iostream>
#include <fstream>
using namespace std;

char szBuf[256][256];
char rBuf[256][256];
int szCount = 0;
ifstream inFile("data.csv");
ofstream outFile("CodeGengerator.h");

void MyGetLine(int num)
{
	for (int i = 0; i < num; i++)
	{
		inFile.getline(rBuf[i], 256);
	}
}

void CommaCheck()
{
	int flag = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < sizeof(rBuf[i]); j++)
		{
			if (rBuf[i][j] == ',')
			{
				for (int k = flag; k < j; k++)
				{
					szBuf[szCount][k] = rBuf[i][k];
				}
				szCount++;
				flag = j;
			}
		}
	}
}

void Parsing()
{
	MyGetLine(2);

	outFile << "struct data" << endl;
	outFile << "{" << endl;

	//for (int i = 0; i < sizeof(szBuf); i++)
	//{
	//	if (szBuf[i] == ',')
	//	{
	//		for (int j = 0; j < i; j++)
	//		{
	//			//rBuf[j] = szBuf[j];
	//		}
	//		outFile << rBuf << " ";
	//		break;
	//	}
	//}

	//ifstream inFile("data.csv");
	//MyGetLine(1);

	//for (int i = 0; i < sizeof(szBuf); i++)
	//{
	//	if (szBuf[i] == ',')
	//	{
	//		for (int j = 0; j < i; j++)
	//		{
	//			//rBuf[j] = szBuf[j];
	//		}
	//		outFile << rBuf << " ";
	//		break;
	//	}
	//}

	/*outFile << "struct data" << endl;
	outFile << "{" << endl;
	outFile << rBuf << " ";*/
}

int main()
{
	//MyGetLine(2);
	//CommaCheck();
	//Parsing();

	MyGetLine(3);
	CommaCheck();
	cout << szBuf[1];

	return 0;
}