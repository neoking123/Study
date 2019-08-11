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
}

void Parsing()
{
	outFile << "struct data" << endl;
	outFile << "{" << endl;
	outFile << '\t' << szBuf[5] << " " << szBuf[0] << " " << "//" << szBuf[10] << endl;
	outFile << '\t' << szBuf[6] << " " << szBuf[1] << " " << "//" << szBuf[11] << endl;
	outFile << '\t' << szBuf[7] << " " << szBuf[2] << " " << "//" << szBuf[12] << endl;
	outFile << '\t' << szBuf[7] << " " << szBuf[3] << " " << "//" << szBuf[13] << endl;
	outFile << '\t' << szBuf[7] << " " << szBuf[4] << " " << "//" << szBuf[14] << endl;
	outFile << "}" << endl;
}

int main()
{
	//MyGetLine(2);
	//CommaCheck();
	//Parsing();

	MyGetLine(3);
	CommaCheck();
	Parsing();

	/*for (int i = 0; i < 15; i++)
	{
		cout << szBuf[i] << " ";
	}*/

	return 0;
}