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
		cout << "\n\n\n\t\t\t\t1. ���� �����" << endl;
		cout << "\n\n\n\t\t\t\t2. �ҷ�����" << endl;
		cout << "\n\n\n\t\t\t\t3. ����" << endl;

		cin >> menuInput;
		if (menuInput == 1)
		{
			system("cls");
			cout << "\n\n\n\t\t\t\t���ο� ���� �����մϴ�." << endl;
			cout << "\n\n\n\t\t\t\t���� ũ�⸦ �Է��ϼ���." << endl;
			cout << "\n\n\n\t\t\t\t���� : ";
			cin >> mapWidth;
			cout << "\n\n\n\t\t\t\t���� : ";
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
					cout << "������ ���ϸ��� �Է��ϼ��� : ";
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

					cout << "���� �Ϸ�" << endl;
				}
			}
		}
		else if (menuInput == 2)
		{
			system("cls");
			cout << endl;
			cout << "������ ���ϸ��� �Է��ϼ��� : ";

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