#include "Scene.h"
#include "Player.h"
#include "Monster.h"

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
	cout << "※※※플레이어 메뉴※※※\n\n\t";
	cout << "□□□□□상태창□□□□□\n\t";
	cout << "□\n\t";
	cout << "□  캐릭터 이름 : " << player->GetName() << "\n\t";
	cout << "□  ● LEVEL : " << player->GetLevel() << "\n\t";
	cout << "□  ● EXP : " << player->GetExp() << "\n\t";
	cout << "□  ● HP : " << player->GetHp() << "\n\t";
	cout << "□  ● MP : " << player->GetMp() << "\n\t";
	cout << "□  ● ATK : " << player->GetAtk() << "\n\t";
	cout << "□  ● DEF : " << player->GetDef() << "\n\t";
	cout << "□\n\t";
	cout << "□□□□□□□□□□□□□";
	cout << "\n\n\t  1. 타이틀 화면으로";
	cout << "\n\n\t  2. 저장";
	cout << "\n\n\t  3. 종료";
	cout << "\n\n\t  4. 돌아가기";
	cout << "\n\n\t  입력 : ";
}

void Scene::printBattleStart()
{
	string battleLog = monster->name + "(이)가 싸움을 걸어왔다!";
	system("cls");
	cout << "\n\n\t" << "NAME : " << monster->name << "  HP : " << monster->hp << "  ATK : " << monster->atk << "  DEF : " << monster->def;
	cout <<	"\n\n\n\n\n\n\n\n\n";
	cout << "\n\n\t" << "NAME : " << player->GetName() << "  HP : " << player->GetHp() << "  ATK : " << player->GetAtk() << "  DEF : " << player->GetDef();
	cout <<	"\n\n";
	cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
	cout << "□\n";
	cout << "□" << "\t" << battleLog << endl;
	cout << "□\n";
	cout << "□\n";
	cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
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
		cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
		cout << "□\n";
		cout << "□" << "\t1. 일반 공격" << endl;
		cout << "□\n";
		cout << "□\n";
		cout << "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n";
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
		//cout << "맵 로딩 완료" << endl;
		//system("pause");
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
