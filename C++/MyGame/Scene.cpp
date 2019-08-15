#include "Scene.h"

void Scene::printTitle()
{
	system("cls");
	cout << "\n\n\n\n\n\t\t\t\t���������";
	cout << "\n\t\t\t\t������  �����";
	cout << "\n\t\t\t\t���������";
	cout << "\n\n\n\n\n\n\n\t\t\t����Ϸ��� �ƹ�Ű�� ��������.";
	_getch();
	//system("pause");
}

void Scene::printIntro()
{
	system("cls");
	cout << "\n\n\n\n\n\t\t�� ������ ������ ������ ��Ÿ���� �ȴ�.";
	cout << "\n\n\n\n\n\t\t���� ������� ������ ��� ��縸�� ��ٷȴ�.";
	cout << "\n\n\n\n\n\t\t��ħ�� ��� ���...";
	cout << "\n\n\n\n\n\t\t���� ������ ��� �� ������..?";
	cout << "\n\n\n\n\n\n";
	_getch();
}

void Scene::printEnd()
{
	system("cls");
	cout << "\n\n\n\n\n\t\t��ħ�� ���� ������ ���񷶴�.";
	cout << "\n\n\n\n\n\t\t���� ������� ȯ���� ������ ������ ��ȯ�ߴ�.";
	cout << "\n\n\n\n\n\t\t���� ������ ������ �Ǿ� �������� ���� �Ǿ���.";
	cout << "\n\n\n\n\n\n";
	_getch();
}

void Scene::printMenu()
{
	system("cls");
	cout << "\n\n\n\n\n\t\t\t\t1. �����ϱ�";
	cout << "\n\n\n\t\t\t\t2. �ҷ�����";
	cout << "\n\n\n\t\t\t\t3. ����" << endl;
}

void Scene::printField()
{
	maps[currentMapName]->Draw();
}

bool Scene::LoadMap(string fileName)
{
	ifstream inFile(fileName);
	if (inFile)
	{
		maps.push_back(new Map());
		string readString;
		stringstream ss;

		getline(inFile, readString);
		ss.str(readString);
		ss >> mapWidth;
		ss.clear();

		getline(inFile, readString);
		ss.str(readString);
		ss >> mapHeight;

		maps.back()->Init(mapWidth, mapHeight);

		char* tok = nullptr;

		for (int i = 0; i < mapHeight; i++)
		{
			getline(inFile, readString);
			tok = strtok((char*)readString.c_str(), ",");
			while (tok != nullptr)
			{
				for (int j = 0; j < mapWidth; j++)
				{
					maps.back()->EditMap(j, i, (EMapState)atoi(tok));
					tok = strtok(nullptr, ",");
				}
			}
		}

		return true;
	}
	else
	{
		cout << "LOAD ERROR : �� ������ �о�� �� �����ϴ�." << endl;
		system("pause");
		return false;
	}
}

Scene::Scene()
{
	sceneType = ESceneType::NONE;
	mapWidth = 0;
	mapHeight = 0;
}

Scene::Scene(ESceneType sceneType)
{
	this->sceneType = sceneType;
}


Scene::~Scene()
{
}

void Scene::Draw()
{
	switch (sceneType)
	{
		case ESceneType::NONE:
			system("cls");
			break;
		case ESceneType::TITLE:
			printTitle();
			break;
		case ESceneType::MENU:
			printMenu();
			break;
		case ESceneType::INTRO:
			printIntro();
			break;
		case ESceneType::END:
			printEnd();
			break;
		case ESceneType::FIELD:
			printField();
			break;
		case ESceneType::BATTLE:
			break;
		case ESceneType::PLAYERMENU:
			break;
		default:
			break;
	}
}
