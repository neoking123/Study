#include <iostream>
#include <fstream>
using namespace std;

char szBuf[256][256];
char rBuf[256][256];
int szCount = 0;	
int colCount = 0;
ifstream inFile("data.csv");
ofstream outFile("CodeGengerator.h");

// 한줄씩 읽어서 배열에 저장
void MyGetLine(int lineCount)
{
	for (int i = 0; i < lineCount; i++)
	{
		inFile.getline(rBuf[i], 256);
	}
}

// 콤마 단위로 끊어서 배열에 저장, 행의 원소 수 리턴
int CommaCheck(int lineCount)
{
	int flag = 0;
	colCount = 0;
	for (int i = 0; i < lineCount; i++)
	{
		flag = 0;
		for (int j = 0; j < sizeof(rBuf[i]); j++)
		{
			if (rBuf[i][j] == ',' || rBuf[i][j] == '\0')
			{
				int l = 0;
				for (int k = flag; k < j; k++)
				{
					szBuf[szCount][l++] = rBuf[i][k];
				}
				szCount++;
				flag = j + 1;
				if (rBuf[i][j] == '\0')
					break;
			}
		}
	}

	return colCount = szCount / lineCount;
}

// 문자 파싱
void Parsing()
{
	outFile << "struct data" << endl;
	outFile << "{" << endl;

	for (int i = 0; i < colCount; i++)
	{
		outFile << '\t' << szBuf[i + colCount] << " " << szBuf[i] << " " << "//" << szBuf[i + colCount * 2] << endl;
	}

	/*outFile << '\t' << szBuf[5] << " " << szBuf[0] << " " << "//" << szBuf[10] << endl;
	outFile << '\t' << szBuf[6] << " " << szBuf[1] << " " << "//" << szBuf[11] << endl;
	outFile << '\t' << szBuf[7] << " " << szBuf[2] << " " << "//" << szBuf[12] << endl;
	outFile << '\t' << szBuf[8] << " " << szBuf[3] << " " << "//" << szBuf[13] << endl;
	outFile << '\t' << szBuf[9] << " " << szBuf[4] << " " << "//" << szBuf[14] << endl;*/

	outFile << "}" << endl;
}



int main()
{
	MyGetLine(3);
	CommaCheck(3);
	Parsing();
	
	return 0;
}