#include "Map.h"

Map map;
int mapWidth = 0;
int mapHeight = 0;

void SaveFile()
{
	string fileName;
	cout << endl;
	cout << "������ ���ϸ��� �Է��ϼ��� : ";
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

	cout << "���� �Ϸ�" << endl;
	_getch();
}

bool LoadFile()
{
	system("cls");
	cout << endl;
	cout << "�ҷ��� ���ϸ��� �Է��ϼ��� : ";
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
			tok = strtok((char*)readString.c_str(), ","); // ","�� �����ϰ� �о����
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
		cout << "������ �������� �ʽ��ϴ�. ���ϸ��� Ȯ���� �ּ���." << endl;
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
		cout << "\n\n\n\t\t\t\t1. ���� �����" << endl;
		cout << "\n\n\n\t\t\t\t2. �ҷ�����" << endl;
		cout << "\n\n\n\t\t\t\t3. ����" << endl;
		cursorInput = 0;

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