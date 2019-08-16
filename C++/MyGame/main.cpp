#include <iostream>
#include "SceneManager.h"
#include "Player.h"
#include "Monster.h"

int main()
{
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
		
		cout << "\n\n\t\t\t\t�Է� : ";
		cin >> menuInput;

		// �����ϱ�
		if (menuInput == 1)
		{
			sceneManager.currentScene = ESceneType::INTRO;
			sceneManager.DrawScene();
			//system("cls");

			// �� �ε�
			if (sceneManager.scenes[ESceneType::FIELD]->LoadMap("village.txt")
				&& sceneManager.scenes[ESceneType::FIELD]->LoadMap("battlezone.txt")
				&& sceneManager.scenes[ESceneType::FIELD]->LoadMap("bossroom.txt"))
			{
				sceneManager.currentScene = ESceneType::FIELD;
			}
			
			// ĳ���� ����
			Player* player = new Player();
			string playerName;
			cout << "\t\t\t������ �̸��� �Է��ϼ��� : ";
			cin >> playerName;
			player->Init(playerName, 100, 100, 1, 1, 0, 1, sceneManager.scenes[ESceneType::FIELD]->maps[EMap::VILLAGE]);
			sceneManager.SetPlayer(player);

			// ���� ����
			Monster* monster = new Monster();
			monster->Init("�ذ�", 30, 10, 10,10, sceneManager.scenes[ESceneType::FIELD]->maps[EMap::BATTLEZONE]);
			sceneManager.SetMonster(monster);

			// In Game Update
			while (true)
			{
				sceneManager.DrawScene();
				if (player->Input() == EKey::CANCLE)
				{
					ESceneType prevScene = sceneManager.currentScene;
					sceneManager.currentScene = ESceneType::PLAYERMENU;
					sceneManager.scenes[ESceneType::PLAYERMENU]->player = sceneManager.GetPlayer();
					sceneManager.DrawScene();

					//_getch();
					int playerMenuInput;
					cin >> playerMenuInput;

					// Ÿ��Ʋ
					if (playerMenuInput == 1)
					{
						break;
					}
					// ����
					else if (playerMenuInput == 2)
					{

					}
					// ����
					else if (playerMenuInput == 3)
					{
						return 0;
					}
					// ���ư���
					else if (playerMenuInput == 4)
					{
						sceneManager.currentScene = prevScene;
						sceneManager.DrawScene();
					}
				}
				else
				{
					sceneManager.CheckPlayerPosition(*player);
				}
			}
		}
		// �ҷ�����
		else if (menuInput == 2)
		{

		}
		else if (menuInput == 3)
		{
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t������ ����ּż� �����մϴ�.";
			cout << "\n\n\n\n\n\n\n\n";
			break;
		}
	}

	return 0;
}