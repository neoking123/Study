#pragma once
#include <windows.h>
#include <vector>
#include <deque>
#include "Macro.h"
using namespace std;

class PlayerInputComponent;
class GameObject;
class Character;
class Camera;
class Background;
class FireRing;
class FirePot;

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
	deque<FireRing*> fireRings;
	vector<GameObject*> colliders;
	FirePot* firePot;
	int fireRingSpawnTime;
	int currentSpawnTime;

	void SpawnFireRing(int x);
	void RandomSpawnFireRing();
	void CheckCameraBoundary();

public:
	~CircusGame();
	void Init(HDC hdc, SIZE gameSize);
	void Update();
	void Draw(HDC hdc);
	void Release();
	vector<GameObject*> GetAllColliders();

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

