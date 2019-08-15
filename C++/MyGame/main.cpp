#include <iostream>
#include "SceneManager.h"
#include "Player.h"

int main()
{
	SceneManager sceneManager;
	sceneManager.Init();
	int menuInput = -1;

	while (true)
	{
		sceneManager.currentScene = ESceneType::TITLE;
		sceneManager.DrawScene();

		sceneManager.currentScene = ESceneType::MENU;
		sceneManager.DrawScene();

		cin >> menuInput;

		// �����ϱ�
		if (menuInput == 1)
		{
			sceneManager.currentScene = ESceneType::INTRO;
			sceneManager.DrawScene();
			system("cls");

			// �� �ε�
			if (sceneManager.scenes[ESceneType::FIELD]->LoadMap("village.txt")
				&& sceneManager.scenes[ESceneType::FIELD]->LoadMap("battlezone.txt"))
			{
				sceneManager.currentScene = ESceneType::FIELD;
				
			}
			
			// ĳ���� ����
			Player player;
			player.Init(100, 100, 1, 1, 0, 1, sceneManager.scenes[ESceneType::FIELD]->maps[EMap::VILLAGE]);

			// In Game Update
			while (true)
			{
				sceneManager.DrawScene();
				player.Input();
				sceneManager.CheckPlayerPosition(player);

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