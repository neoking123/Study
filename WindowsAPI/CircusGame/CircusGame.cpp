#include "CircusGame.h"
#include "BitMapManager.h"
#include "PlayerInputComponent.h"
#include "Character.h"
#include "Camera.h"
#include "Background.h"
#include "FireRing.h"
#include "FirePot.h"

CircusGame* CircusGame::pInstance = nullptr;

CircusGame::CircusGame()
{
}

void CircusGame::SpawnFireRing(int x)
{
	FireRing* fireRing = new FireRing();
	fireRing->Init(x, 330);
	fireRings.push_back(fireRing);
	gameObjects.push_back(fireRing);
	colliders.push_back(fireRing);
}

void CircusGame::SpawnFirePot(int x)
{
	FirePot* newFirePot = new FirePot();
	newFirePot->Init(x, 485);
	gameObjects.push_back(newFirePot);
	firePots.push_back(newFirePot);
	colliders.push_back(newFirePot);
}

void CircusGame::RandomSpawnFireRing()
{
	if (currentSpawnTime > fireRingSpawnTime)
	{
		SpawnFireRing(4000 + camera->GetSize().cx);
		fireRingSpawnTime = rand() % 200 + 400;
		currentSpawnTime = 0;
	}

	currentSpawnTime++;
}

void CircusGame::CheckCameraBoundary()
{

	deque<FireRing*>::iterator iter = fireRings.begin();
	for (; iter != fireRings.end(); iter++)
	{
		FireRing* fireRing = static_cast<FireRing*>(*iter);
		if (fireRing->transform.position.x < camera->transform.position.x - camera->GetSize().cx / 2)
		{
			break;
		}
	}

	if (iter != fireRings.end())
	{
		fireRings.pop_front();
		deque<GameObject*>::iterator iter = colliders.begin();
		for(; iter != colliders.end(); iter++)
		{
			if ((*iter)->tag == "FireRing")
			{
				break;
			}
		}

		if (iter != colliders.end())
		{
			colliders.erase(iter);
		}
	}
}

CircusGame::~CircusGame()
{
}

void CircusGame::Init(HDC hdc, SIZE gameSize)
{
	gameDCSize = gameSize;
	gameDC = CreateCompatibleDC(hdc);
	hBitMap = CreateCompatibleBitmap(hdc, gameDCSize.cx, gameDCSize.cy);
	hOldBitMap = (HBITMAP)SelectObject(gameDC, hBitMap);
	BitMapManager::GetInstance()->Init(gameDC);

	gameObjects.reserve(1000);

	//ĳ����
	playerInput = new PlayerInputComponent();
	player = new Character();
	player->Init(playerInput, 100, 485);
	gameObjects.push_back(player);

	//ī�޶�
	camera = new Camera();
	camera->Init(gameDC, SIZE{ 800, 600 }, 400, 300);
	gameObjects.push_back(camera);
	camera->SetTarget(*player);

	//���ȭ��
	background = new Background();
	background->Init();

	fireRingSpawnTime = 10;
	currentSpawnTime = 0;

	//�Ҹ�
	int lastpos = 800;
	for (int i = 0; i < 12; i++)
	{
		int randomDist = rand() % 200 + 200;
		lastpos += randomDist;
		SpawnFireRing(lastpos);
	}

	int distance = 1850;
	for (int i = 0; i < 5; i++)
	{
		distance += 450;
		SpawnFirePot(distance);
	}
	SpawnFirePot(4500);
}

void CircusGame::Update()
{
	background->Update(gameDC, *camera);
	RandomSpawnFireRing();

	//�Ҹ� ��ü
	for (auto iter = fireRings.begin(); iter != fireRings.end(); iter++)
	{
		(*iter)->Update(gameDC);
	}

	//�Ҵ���
	for (auto iter = firePots.begin(); iter != firePots.end(); iter++)
	{
		(*iter)->Update(gameDC);
	}

	player->Update(gameDC);

	//�Ҹ� �޺κ�
	for (auto iter = fireRings.begin(); iter != fireRings.end(); iter++)
	{
		(*iter)->DrawBack(gameDC);
	}

	CheckCameraBoundary();

	//ī�޶�� ���� ���������� ������Ʈ
	camera->Update(gameDC);
}

void CircusGame::Draw(HDC hdc)
{
	BitBlt(hdc, 0, 0, camera->GetSize().cx, camera->GetSize().cy, camera->GetDC(), 0, 0, SRCCOPY);
}

void CircusGame::Release()
{
	SelectObject(gameDC, hOldBitMap);
	DeleteObject(hBitMap);
	DeleteDC(gameDC);

	SAFE_DELETE(playerInput);
	SAFE_DELETE(camera);

	for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
	{
		SAFE_DELETE(*iter);
	}
}

deque<GameObject*> CircusGame::GetAllColliders()
{
	return colliders;
}
