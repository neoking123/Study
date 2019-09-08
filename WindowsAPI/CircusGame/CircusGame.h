#pragma once
#include <windows.h>
#include <vector>
#include "Macro.h"
using namespace std;

class PlayerInputComponent;
class GameObject;
class Character;
class Camera;
class Background;

class CircusGame
{
private:
	CircusGame();

	static CircusGame* pInstance;

	HDC gameDC;
	SIZE gameDCSize;
	HBITMAP hBitMap;
	HBITMAP hOldBitMap;

	vector<GameObject*> gameObjects;
	PlayerInputComponent* playerInput;
	Character* player;
	Camera* camera;
	Background* background;

public:
	~CircusGame();
	void Init(HDC hdc, SIZE gameSize);
	void Update();
	void Draw(HDC hdc);
	void Input(UINT iMessage, WPARAM wParam);
	void Release();
	vector<GameObject*> GetAllObjects();

	static CircusGame* GetInstance()
	{
		if (pInstance == nullptr)
		{
			pInstance = new CircusGame();
		}
		return pInstance;
	}

	static void FreeInstance()
	{
		SAFE_DELETE(pInstance);
	}
};

