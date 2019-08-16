#include "Scene.h"
#include "Player.h"
#include "Monster.h"

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
	_getch();
}

void Scene::printField()
{
	if (currentMapName <= EMap::BOSSROOM && currentMapName >= EMap::VILLAGE)
	{
		maps[currentMapName]->Draw();
	}
}

void Scene::printPlayerMenu()
{
	system("cls");
	cout << "\n\n\t";
	cout << "�ءء��÷��̾� �޴��ءء�\n\n\t";
	cout << "���������â������\n\t";
	cout << "��\n\t";
	cout << "��  ĳ���� �̸� : " << player->GetName() << "\n\t";
	cout << "��  �� LEVEL : " << player->GetLevel() << "\n\t";
	cout << "��  �� EXP : " << player->GetExp() << "\n\t";
	cout << "��  �� HP : " << player->GetHp() << "\n\t";
	cout << "��  �� MP : " << player->GetMp() << "\n\t";
	cout << "��  �� ATK : " << player->GetAtk() << "\n\t";
	cout << "��  �� DEF : " << player->GetDef() << "\n\t";
	cout << "��\n\t";
	cout << "��������������";
	cout << "\n\n\t  1. Ÿ��Ʋ ȭ������";
	cout << "\n\n\t  2. ����";
	cout << "\n\n\t  3. ����";
	cout << "\n\n\t  4. ���ư���";
	cout << "\n\n\t  �Է� : ";
}

void Scene::printBattleStart()
{
	string battleLog = monster->name + "(��)�� �ο��� �ɾ�Դ�!";
	system("cls");
	cout << "\n\n\t" << "NAME : " << monster->name << "  HP : " << monster->hp << "  ATK : " << monster->atk << "  DEF : " << monster->def;
	cout <<	"\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\t" << "NAME : " << player->GetName() << "  HP : " << player->GetHp() << "  ATK : " << player->GetAtk() << "  DEF : " << player->GetDef();
	cout <<	"\n\n";
	cout << "����������������������������������������\n";
	cout << "��\n";
	cout << "��" << "\t" << battleLog << endl;
	cout << "��\n";
	cout << "��\n";
	cout << "����������������������������������������\n";
}

void Scene::printBattleIng()
{
	string battleLog;

	while (true)
	{
		system("cls");
		cout << "\n\n\t" << "NAME : " << monster->name << "  HP : " << monster->hp << "  ATK : " << monster->atk << "  DEF : " << monster->def;
		cout << "\n\n\n\n\n\n\n\n\n";
		cout << "\n\n\t" << "NAME : " << player->GetName() << "  HP : " << player->GetHp() << "  ATK : " << player->GetAtk() << "  DEF : " << player->GetDef();
		cout << "\n\n";
		cout << "����������������������������������������\n";
		cout << "��\n";
		cout << "��" << "\t1. �Ϲ� ����" << endl;
		cout << "��\n";
		cout << "��\n";
		cout << "����������������������������������������\n";
	}
}

bool Scene::LoadMap(string fileName)
{
	ifstream inFile(fileName);
	if (inFile)
	{
		Map* newMap = new Map();
		maps.push_back(newMap);
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
		char* context = nullptr;

		for (int i = 0; i < mapHeight; i++)
		{
			getline(inFile, readString);
			tok = strtok_s((char*)readString.c_str(), ",", &context);
			while (tok != nullptr)
			{
				for (int j = 0; j < mapWidth; j++)
				{
					maps.back()->EditMap(j, i, (EMapState)atoi(tok));
					tok = strtok_s(nullptr, ",", &context);
				}
			}
		}
		//cout << "�� �ε� �Ϸ�" << endl;
		//system("pause");
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
	currentMapName = EMap::VILLAGE;
	mapWidth = 0;
	mapHeight = 0;
	maps.reserve(10);
	player = nullptr;
}

Scene::Scene(ESceneType sceneType) : Scene()
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
			printBattleStart();
			printBattleIng();
			break;
		case ESceneType::PLAYERMENU:
			printPlayerMenu();
			break;
		default:
			break;
	}
}
