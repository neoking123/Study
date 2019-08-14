#include "Map.h"

int main()
{
	Map map;
	int mapWidth = 0;
	int mapHeight = 0;
	int menuInput = 0;
	char cursorInput = 0;

	while (true)
	{
		system("cls");
		cout << "\n\n\n\t\t\t\t1. 새로 만들기" << endl;
		cout << "\n\n\n\t\t\t\t2. 불러오기" << endl;
		cout << "\n\n\n\t\t\t\t3. 종료" << endl;

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

			while (cursorInput != 'p')
			{
				map.Draw();
				map.PrintMenu();
				cursorInput = map.InputCursor();

				if (cursorInput == 'o')
				{
					string fileName;
					cout << endl;
					cout << "저장할 파일명을 입력하세요 : ";
					cin >> fileName;
					ofstream outFile(fileName + ".txt");

					for (int i = 0; i < mapHeight; i++)
					{
						for (int j = 0; j < mapWidth; j++)
						{
							outFile << map.GetMapState(j, i) << ",";
						}
						outFile << endl;
					}

					cout << "저장 완료" << endl;
				}
			}
		}
		else if (menuInput == 2)
		{
			system("cls");
			cout << endl;
			cout << "저장할 파일명을 입력하세요 : ";

			string fileName;
			ifstream inFile("data.csv");
		}
		else if (menuInput == 3)
		{
			break;
		}
	}

	return 0;
}