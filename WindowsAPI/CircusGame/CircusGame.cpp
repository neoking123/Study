#include "CircusGame.h"
#include "BitMapManager.h"
#include "PlayerInputComponent.h"
#include "Character.h"
#include "Camera.h"
#include "Background.h"
#include "FireRing.h"

CircusGame* CircusGame::pInstance = nullptr;

CircusGame::CircusGame()
{
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

	colliders.reserve(100);

	//�Ҹ�
	FireRing* fireRing = new FireRing();
	fireRing->Init(500, 330);
	fireRings.push_back(fireRing);
	gameObjects.push_back(fireRing);
	colliders.push_back(fireRing);
}

void CircusGame::Update()
{
	background->Update(gameDC, *camera);

	for (auto iter = fireRings.begin(); iter != fireRings.end(); iter++)
	{
		(*iter)->Update(gameDC);
	}

	player->Update(gameDC);

	//�Ҹ� �޺κ�
	for (auto iter = fireRings.begin(); iter != fireRings.end(); iter++)
	{
		(*iter)->DrawBack(gameDC);
	}

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

vector<GameObject*> CircusGame::GetAllColliders()
{
	return colliders;
}
