#include "Map.h"

Map map;
int mapWidth = 0;
int mapHeight = 0;

void SaveFile()
{
	string fileName;
	cout << endl;
	cout << "저장할 파일명을 입력하세요 : ";
	cin >> fileName;
	ofstream outFile(fileName + ".txt");

	outFile << mapWidth << endl;
	outFile << mapHeight << endl;

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			outFile << map.GetMapState(j, i) << ",";
		}
		outFile << endl;
	}

	cout << "저장 완료" << endl;
	_getch();
}

bool LoadFile()
{
	system("cls");
	cout << endl;
	cout << "불러올 파일명을 입력하세요 : ";
	string fileName;
	cin >> fileName;

	ifstream inFile(fileName + ".txt");
	if (inFile)
	{
		string readString;
		stringstream ss;

		getline(inFile, readString);
		ss.str(readString);
		ss >> mapWidth;
		ss.clear();

		getline(inFile, readString);
		ss.str(readString);
		ss >> mapHeight;

		map.Init(mapWidth, mapHeight);
		map.CreateCursor();

		char* tok = nullptr;

		for (int i = 0; i < mapHeight; i++)
		{
			getline(inFile, readString);
			tok = strtok((char*)readString.c_str(), ","); // ","를 제외하고 읽어들임
			while (tok != nullptr)
			{
				for (int j = 0; j < mapWidth; j++)
				{
					map.EditMap(j, i, (EMapState)atoi(tok));
					tok = strtok(nullptr, ",");
				}
			}
		}

		return true;
	}
	else
	{
		cout << "파일이 존재하지 않습니다. 파일명을 확인해 주세요." << endl;
		return false;
	}
}

int main()
{
	int menuInput = 0;
	char cursorInput;

	while (true)
	{
		system("cls");
		cout << "\n\n\n\t\t\t\t1. 새로 만들기" << endl;
		cout << "\n\n\n\t\t\t\t2. 불러오기" << endl;
		cout << "\n\n\n\t\t\t\t3. 종료" << endl;
		cursorInput = 0;

		cin >> menuInput;
		if (menuInput == 1)
		{
			system("cls");
			cout << "\n\n\n\t\t\t\t새로운 맵을 생성합니다." << endl;
			cout << "\n\n\n\t\t\t\t맵의 크기를 입력하세요." << endl;
			cout << "\n\n\n\t\t\t\t가로 : ";
			cin >> mapWidth;
			cout << "\n\n\n\t\t\t\t세로 : ";
			cin >> mapHeight;

			map.Init(mapWidth, mapHeight);
			map.CreateCursor();

			while (cursorInput != 'q')
			{
				map.Draw();
				map.PrintMenu();
				cursorInput = map.InputCursor();

				if (cursorInput == 'w')
				{
					SaveFile();
					map.DeleteCursor();
					break;
				}
				else if (cursorInput == 'q')
				{
					map.DeleteCursor();
				}
			}
		}
		else if (menuInput == 2)
		{
			if (LoadFile())
			{
				while (cursorInput != 'q')
				{
					map.Draw();
					map.PrintMenu();
					cursorInput = map.InputCursor();

					if (cursorInput == 'w')
					{
						SaveFile();
						map.DeleteCursor();
						break;
					}
					else if (cursorInput == 'q')
					{
						map.DeleteCursor();
					}
				}
			}
		}
		else if (menuInput == 3)
		{
			break;
		}
	}

	return 0;
}