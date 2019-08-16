#include <iostream>
#include "SceneManager.h"
#include "Player.h"
#include "Monster.h"
#include "Boss.h"
#include <time.h>

int main()
{
	srand(time(nullptr));
	/*SceneManager sceneManager;
	sceneManager.Init();
	int menuInput = -1;*/

	while (true)
	{
		SceneManager sceneManager;
		sceneManager.Init();
		int menuInput = -1;

		sceneManager.currentScene = ESceneType::TITLE;
		sceneManager.DrawScene();

		sceneManager.currentScene = ESceneType::MENU;
		sceneManager.DrawScene();
		
		cout << "\n\n\t\t\t\t입력 : ";
		cin >> menuInput;

		// 새로하기
		if (menuInput == 1)
		{
			sceneManager.currentScene = ESceneType::INTRO;
			sceneManager.DrawScene();
			//system("cls");

			// 맵 로딩
			if (sceneManager.scenes[ESceneType::FIELD]->LoadMap("village.txt")
				&& sceneManager.scenes[ESceneType::FIELD]->LoadMap("battlezone.txt")
				&& sceneManager.scenes[ESceneType::FIELD]->LoadMap("bossroom.txt"))
			{
				sceneManager.currentScene = ESceneType::FIELD;
			}
			
			// 캐릭터 생성
			Player* player = new Player();
			string playerName;
			cout << "\t\t\t용사님의 이름을 입력하세요 : ";
			cin >> playerName;
			player->Init(playerName, 100, 100, 20, 10, 0, 1, sceneManager.scenes[ESceneType::FIELD]->maps[EMap::VILLAGE]);
			sceneManager.SetPlayer(player);

			// 몬스터 생성
			Monster* monster = new Monster();
			monster->Init("해골", 50, 30, 10,10, sceneManager.scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE]);
			sceneManager.SetMonster(monster);

			// 보스 생성
			Boss* boss = new Boss();
			boss->Init("보스", 200, 50, 15, 100, sceneManager.scenes[ESceneType::FIELD]->maps[EMap::BOSSROOM]);
			sceneManager.SetBoss(boss);

			// In Game Update
			while (true)
			{
				sceneManager.CheckSceneType();
				sceneManager.DrawScene();

				if (player->Input() == EKey::CANCLE)
				{
					sceneManager.prevtScene = sceneManager.currentScene;
					sceneManager.currentScene = ESceneType::PLAYERMENU;
					sceneManager.scenes[ESceneType::PLAYERMENU]->player = sceneManager.GetPlayer();
					sceneManager.DrawScene();

					//_getch();
					int playerMenuInput;
					cin >> playerMenuInput;

					// 타이틀
					if (playerMenuInput == 1)
					{
						break;
					}
					// 저장
					else if (playerMenuInput == 2)
					{

					}
					// 종료
					else if (playerMenuInput == 3)
					{
						return 0;
					}
					// 돌아가기
					else if (playerMenuInput == 4)
					{
						sceneManager.currentScene = sceneManager.prevtScene;
						sceneManager.DrawScene();
					}
				}
				else
				{
					sceneManager.CheckPlayerPosition(*player);
				}
			}
		}
		// 불러오기
		else if (menuInput == 2)
		{

		}
		else if (menuInput == 3)
		{
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t게임을 즐겨주셔서 감사합니다.";
			cout << "\n\n\n\n\n\n\n\n";
			break;
		}
	}

	return 0;
}