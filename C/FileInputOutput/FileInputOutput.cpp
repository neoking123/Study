#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ofstream outFile("a.txt", ios::out);
	outFile << "sdfdsf11123131" << endl;
	outFile.close();

	char szBuf[256];
	ifstream inFile("a.txt");
	inFile >> szBuf;
	cout << szBuf;
	inFile.close();


	////C
	//FILE* p = fopen("a.txt", "r");

	////fprintf(p, "%d", 1);

	//int a = 0;
	////fscanf(p, "%d", &a);

	//char szBuf[256];

	////fwrite(szBuf, sizeof(char), 256, p);

	//fread(szBuf, sizeof(char), 256, p);
	////fseek(p, 4, SEEK_CUR); //SEEK_END, SEEK_SET
	// 
	//cout << szBuf << endl;

	//fclose(p);

	return 0;
}