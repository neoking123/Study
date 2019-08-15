#include "Scene.h"

void Scene::printTitle()
{
	system("cls");
	cout << "\n\n\n\n\n\t\t\t\t■■■■■■■■";
	cout << "\n\t\t\t\t■용사의  모험■";
	cout << "\n\t\t\t\t■■■■■■■■";
	cout << "\n\n\n\n\n\n\n\t\t\t계속하려면 아무키나 누르세요.";
	_getch();
	//system("pause");
}

void Scene::printIntro()
{
	system("cls");
	cout << "\n\n\n\n\n\t\t한 마을에 강력한 보스가 나타나게 된다.";
	cout << "\n\n\n\n\n\t\t마을 사람들은 보스를 무찌를 용사만을 기다렸다.";
	cout << "\n\n\n\n\n\t\t마침내 깨어난 용사...";
	cout << "\n\n\n\n\n\t\t과연 보스를 무찌를 수 있을까..?";
	cout << "\n\n\n\n\n\n";
	_getch();
}

void Scene::printEnd()
{
	system("cls");
	cout << "\n\n\n\n\n\t\t마침내 용사는 보스를 무찔렀다.";
	cout << "\n\n\n\n\n\t\t마을 사람들의 환영을 받으며 마을로 귀환했다.";
	cout << "\n\n\n\n\n\t\t용사는 마을의 전설이 되어 영웅으로 남게 되었다.";
	cout << "\n\n\n\n\n\n";
	_getch();
}

void Scene::printMenu()
{
	system("cls");
	cout << "\n\n\n\n\n\t\t\t\t1. 새로하기";
	cout << "\n\n\n\t\t\t\t2. 불러오기";
	cout << "\n\n\n\t\t\t\t3. 종료" << endl;
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
		cout << "LOAD ERROR : 맵 파일을 읽어올 수 없습니다." << endl;
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
